/*
 * Copyright (C) 2011-2012 Matias Valdenegro <matias.valdenegro@gmail.com>
 * This file is part of KResearch.
 *
 * kesearch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * kresearch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KResearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BibtexParser.h"

#include <QMap>
#include <QStringList>
#include <QDebug>

#include <util/StringUtils.h>
#include <util/NameUtils.h>

BibtexParser::BibtexParser()
{
}

BibtexParser::~BibtexParser()
{
}

inline QString cleanup(const QString& input)
{
    QString tmp = input;
    tmp = tmp.remove('\n');
    tmp = tmp.remove('}');
    tmp = tmp.remove('{');

    return tmp.trimmed();
}

inline QStringList cleanup(const QStringList& input)
{
    QStringList ret;

    for(QString s: input) {
        ret += cleanup(s);
    }

    return ret;
}

static QRegExp entryRegexp = QRegExp("@([a-zA-Z]+)\\s*\\{(.+)\\}");

Document::List BibtexParser::parse(const QString& str) const
{
    Document::List ret;
    int pos = entryRegexp.indexIn(str);

    if(pos == -1) {
        return ret;
    }

    QStringList entries = entryRegexp.capturedTexts();
    //Skip first entry since it contains the whole matched text.
    entries.removeAt(0);

    //Entries size should be a multiple of 2, a pair of bibtex entry type and bibtex entry data.
    if((entries.count() % 2) == 1) {
        return ret;
    }

    for(int i = 0; i < entries.count(); i += 2) {
        QString type = cleanup(entries[i]).toLower();
        QString data = entries[i + 1];

        qDebug() << "Type" << type;
        qDebug() << "Data" << data;

        Document::Ptr document = fillDocumentData(type, data);

        if(document != nullptr) {
            ret.append(document);
        }
    }

    return ret;
}

QString BibtexParser::removeQuotes(const QString& input) const
{
    return QString(input).remove('"').trimmed();
}

typedef QMap<QString, QString> StringMap;

class BibtexDocumentFiller
{
    public:
        BibtexDocumentFiller()
        {
        }

        virtual ~BibtexDocumentFiller()
        {
        }

        virtual Document::Ptr fillDocument(const StringMap& data) const = 0;

        QStringList parseAuthors(const QString& authorString) const
        {
            QStringList tmp = authorString.split("and");
            QStringList ret;

            for(QString rawName: tmp) {
                ret += NameUtils::normalize(rawName);

                qDebug() << "formatted name" << NameUtils::normalize(rawName);
            }

            return cleanup(ret);
        }
};

class BibtexArticleFiller : public BibtexDocumentFiller
{
    public:
        BibtexArticleFiller() {}

        virtual ~BibtexArticleFiller() {}

        virtual Document::Ptr fillDocument(const StringMap& data) const
        {
            Document::Ptr document = new Document();

            //Type
            document->setType(DocumentType::Article);

            //Required fields
            document->setTitle(data["title"]);

            Journal::Ptr journal = new Journal();
            journal->setName(data["journal"]);
            document->setJournal(journal);

            document->setYear(data["year"].toInt());
            document->setAuthors(parseAuthors(data["author"]));

            //Optional fields
            document->setVolume(data["volume"].toInt());
            document->setNumber(data["number"].toInt());

            return document;
        }
};

class BibtexBookFiller : public BibtexDocumentFiller
{
    public:
        BibtexBookFiller() {}

        virtual ~BibtexBookFiller() {}

        virtual Document::Ptr fillDocument(const StringMap& data) const
        {
            Document::Ptr document = new Document();

            //Type
            document->setType(DocumentType::Book);

            //Required fields
            document->setTitle(data["title"]);
            document->setPublisher(data["publisher"]);
            document->setYear(data["year"].toInt());

            if(data.contains("author")) {
                document->setAuthors(parseAuthors(data["author"]));
            } else {
                document->setAuthors(parseAuthors(data["editor"]));
            }

            //Optional fields
            document->setVolume(data["volume"].toInt());
            document->setNumber(data["number"].toInt());

            return document;
        }
};

class BibtexConferenceFiller : public BibtexDocumentFiller
{
    public:
        BibtexConferenceFiller() {}

        virtual ~BibtexConferenceFiller() {}

        virtual Document::Ptr fillDocument(const StringMap& data) const
        {
            Document::Ptr document = new Document();

            //Type
            document->setType(DocumentType::ConferenceArticle);

            //Required fields
            document->setTitle(data["title"]);
            document->setConference(data["booktitle"]);
            document->setYear(data["year"].toInt());
            document->setAuthors(parseAuthors(data["author"]));

            //Optional fields
            document->setVolume(data["volume"].toInt());
            document->setNumber(data["number"].toInt());

            return document;
        }
};

class BibtexNullFiller : public BibtexDocumentFiller
{
    public:
        BibtexNullFiller() {}

        virtual ~BibtexNullFiller() {}

        virtual Document::Ptr fillDocument(const StringMap& data) const
        {
            return nullptr;
        }
};

static BibtexDocumentFiller *nullFiller = new BibtexNullFiller();

inline QMap<QString, BibtexDocumentFiller *> createFillerMap()
{
    QMap<QString, BibtexDocumentFiller *> map;
    map.insert("book"           , new BibtexBookFiller());
    map.insert("article"        , new BibtexArticleFiller());
    map.insert("booklet"        , nullptr);
    map.insert("conference"     , new BibtexConferenceFiller());
    map.insert("inbook"         , nullptr);
    map.insert("incollection"   , nullptr);
    map.insert("inproceedings"  , new BibtexConferenceFiller());
    map.insert("manual"         , nullptr);
    map.insert("masterthesis"   , nullptr);
    map.insert("misc"           , nullptr);
    map.insert("phdthesis"      , nullptr);
    map.insert("proceedings"    , nullptr);
    map.insert("techreport"     , nullptr);
    map.insert("unpublished"    , nullptr);

    return map;
}

static QMap<QString, BibtexDocumentFiller *> fillerMap = createFillerMap();


BibtexDocumentFiller *dispatchFiller(const QString& type)
{
    if(fillerMap.contains(type)) {
        return fillerMap[type];
    }

    return nullFiller;
}

Document::Ptr BibtexParser::fillDocumentData(const QString& type, const QString& rawData) const
{
    QStringList data = StringUtils::splitWithCommas(rawData);
    StringMap dataMap;

    if(data.count() == 0) {
        return nullptr;
    }

    //Assume that the first element
    QString citeKey = data[0];

    qDebug() << "Splitting data" << rawData;

    for(int i = 1; i < data.count(); i++) {
        QStringList parts = data[i].split('=');
        parts = cleanup(parts);

        if(parts.count() != 2) {

            qDebug() << "Parts don't match" << parts;

            return nullptr;
        }

        QString tag = parts[0].toLower();
        QString tagValue = removeQuotes(parts[1]);

        qDebug() << "Tag" << tag;
        qDebug() << "TagValue" << tagValue;

        dataMap.insert(tag, tagValue);
    }

    Document::Ptr document = dispatchFiller(type)->fillDocument(dataMap);

    return document;
}

