/*
 * Copyright (C) 2011-2012 Matias Valdenegro <matias.valdenegro@gmail.com>
 * This file is part of kresearch.
 *
 * kresearch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * kresearch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU  General Public License for more details.
 *
 * You should have received a copy of the GNU  General Public License
 * along with kresearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SQLitePublicationDAO.h"
#include <sqliteLibrary/SQLiteRepository.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

SQLitePublicationDAO::SQLitePublicationDAO(SQLiteRepository *cache)
: PublicationDAO(), SQLiteBaseDAO(cache)
{
}

SQLitePublicationDAO::~SQLitePublicationDAO()
{
}

Publication::Ptr SQLitePublicationDAO::findById(qulonglong id) const
{
    if(repository()->publications()->contains(id)) {
        return repository()->publications()->find(id);
    }

    QSqlQuery query(database());
    bool ok = true;
    ok &= query.prepare("SELECT * FROM publication WHERE id = :id");
    query.bindValue(":id", id);
    ok &= query.exec();

    debug(query);

    if(ok) {

        if(query.next()) {

            QSqlRecord record = query.record();
            qulonglong id = record.value("id").toULongLong();
            Publication::Ptr pub = Publication::Ptr(new Publication());

            pub->setId(id);
            pub->setTitle(record.value("title").toString());
            pub->setAbstract(record.value("abstract").toString());
            pub->setYear(record.value("year").toInt());
            pub->setConference(record.value("conference").toString());
            pub->setJournal(record.value("journal").toString());
            pub->setPublisher(record.value("publisher").toString());
            pub->setSeries(record.value("series").toString());
            pub->setSubseries(record.value("subseries").toString());
            pub->setVolume(record.value("volume").toInt());
            pub->setNumber(record.value("number").toInt());
            pub->setUrl(record.value("url").toString());
            pub->setDoi(record.value("doi").toString());
            pub->setIsbn(record.value("isbn").toString());
            pub->setLocalUrl(record.value("localURL").toString());
            pub->setType(PublicationType::fromUInt(record.value("type").toUInt()));
            pub->setPublished(record.value("isPublished").toBool());
            pub->setPeerReviewed(record.value("isPeerReviewed").toBool());

            repository()->publications()->insert(id, pub);

            IDList idAuthors = authorIDs(id);
            Author::List authors;

            foreach(qulonglong aid, idAuthors) {
                authors.append(repository()->authorDAO()->findById(aid));
            }

            pub->setAuthors(authors);

            emit dataChanged();

            return pub;
        }
    }

    return Publication::Ptr();
}

bool SQLitePublicationDAO::saveOrUpdate(Publication::Ptr pub)
{
    if(!pub) {
        return false;
    }

    const qulonglong invalidId = (qulonglong) -1;

    if(pub->id() == invalidId) {

        return save(pub);
    } else {

        return update(pub);
    }
}

Publication::List SQLitePublicationDAO::findAll() const
{
    return repository()->publications()->findAll();
}

QStringList SQLitePublicationDAO::journals() const
{
    QSqlQuery query(database());
    query.prepare("SELECT DISTINCT journal FROM publication");
    query.exec();

    QStringList ret;

    while(query.next()) {
        QString journalName = query.record().value("journal").toString();

        if(!journalName.isEmpty() && !journalName.isNull()) {
            ret += journalName;
        }
    }

    return ret;
}

QStringList SQLitePublicationDAO::conferences() const
{
    QSqlQuery query(database());
    query.prepare("SELECT DISTINCT conference FROM publication");
    query.exec();

    QStringList ret;

    while(query.next()) {
        QString confName = query.record().value("conference").toString();

        if(!confName.isEmpty() && !confName.isNull()) {
            ret += confName;
        }
    }

    return ret;
}

bool SQLitePublicationDAO::save(Publication::Ptr pub)
{
    if(!pub) {
        return false;
    }

    bool ok = true;
    database().transaction();

    QSqlQuery query(database());
    ok &= query.prepare("INSERT INTO publication(title, abstract, year, conference, journal, publisher, "
                                                "series, subseries, volume, number, url, doi, isbn, localURL,"
                                                "type, isPublished, isPeerReviewed) "
                         "VALUES(:title, :abstract, :year, :conference, :journal, :publisher, "
                                ":series, :subseries, :volume, :number, :url, :doi, :isbn, :localURL,"
                                ":type, :isPublished, :isPeerReviewed)");

    query.bindValue(":title", pub->title());
    query.bindValue(":abstract", pub->abstract());
    query.bindValue(":year", pub->year());
    query.bindValue(":conference", pub->conference());
    query.bindValue(":journal", pub->journal());
    query.bindValue(":publisher", pub->publisher());
    query.bindValue(":series", pub->series());
    query.bindValue(":subseries", pub->subseries());
    query.bindValue(":volume", pub->volume());
    query.bindValue(":number", pub->number());
    query.bindValue(":url", pub->url());
    query.bindValue(":doi", pub->doi());
    query.bindValue(":isbn", pub->isbn());
    query.bindValue(":localURL", pub->localUrl());
    query.bindValue(":type", pub->type().toUInt());
    query.bindValue(":isPublished", pub->isPublished());
    query.bindValue(":isPeerReviewed", pub->isPeerReviewed());
    ok &= query.exec();

    debug(query);

    if(ok) {
        qulonglong id = lastInsertRowID();
        pub->setId(id);

        updateAuthors(pub);

        repository()->publications()->insert(id, pub);
    }

    if(!ok) {
        ok &= database().rollback();
    } else {
        ok &= database().commit();
    }

    emit dataChanged();

    return ok;
}

bool SQLitePublicationDAO::update(Publication::Ptr pub)
{
    if(!pub) {
        return false;
    }

    bool ok = true;

    QSqlQuery query(database());
    ok &= query.prepare("UPDATE publication SET title = :title, abstract = :abstract, year = :year, conference = :conference, journal = :journal,"
                        " publisher = :publisher, series = :series, subseries = :subseries, volume = :volume, number = :number, url = :url, "
                        " doi = :doi, isbn = :isbn, localURL = :localURL, type = :type, isPublished = :isPublished,"
                        " isPeerReviewed = :isPeerReviewed WHERE id = :id");

    query.bindValue(":id", pub->id());
    query.bindValue(":title", pub->title());
    query.bindValue(":abstract", pub->abstract());
    query.bindValue(":year", pub->year());
    query.bindValue(":conference", pub->conference());
    query.bindValue(":journal", pub->journal());
    query.bindValue(":publisher", pub->publisher());
    query.bindValue(":series", pub->series());
    query.bindValue(":subseries", pub->subseries());
    query.bindValue(":volume", pub->volume());
    query.bindValue(":number", pub->number());
    query.bindValue(":url", pub->url());
    query.bindValue(":doi", pub->doi());
    query.bindValue(":isbn", pub->isbn());
    query.bindValue(":localURL", pub->localUrl());
    query.bindValue(":type", pub->type().toUInt());
    query.bindValue(":isPublished", pub->isPublished());
    query.bindValue(":isPeerReviewed", pub->isPeerReviewed());
    ok &= query.exec();

    debug(query);

    updateAuthors(pub);

    emit dataChanged();

    return ok;
}

bool SQLitePublicationDAO::updateAuthors(Publication::Ptr pub)
{
    foreach(Author::Ptr author, pub->authors()) {
        repository()->authorDAO()->saveOrUpdate(author);
    }

    QSet<qulonglong> updatedAuthorIDs = toAuthorSet(pub->authors());
    QSet<qulonglong> storedAuthorIDs = authorIDs(pub->id()).toSet();

    bool ok = true;

    qDebug() << "updatedAuthors" << updatedAuthorIDs;
    qDebug() << "storedAuthors" << storedAuthorIDs;

    qDebug() << "Added authors" << updatedAuthorIDs - storedAuthorIDs;
    qDebug() << "Removed authors" << storedAuthorIDs - updatedAuthorIDs;

    if(updatedAuthorIDs != storedAuthorIDs) {

        QSqlQuery query(database());
        ok &= query.prepare("DELETE FROM publication_author WHERE publicationId = :publicationId");
        query.bindValue(":publicationId", pub->id());
        ok &= query.exec();

        debug(query);

        foreach(qulonglong aid, updatedAuthorIDs) {

            QSqlQuery insert(database());
            ok &= insert.prepare("INSERT INTO publication_author(publicationId, authorId) VALUES(:publicationId, :authorId)");
            insert.bindValue(":publicationId", pub->id());
            insert.bindValue(":authorId", aid);
            ok &= insert.exec();

            debug(insert);
        }
    }

    return true;
}

IDList SQLitePublicationDAO::authorIDs(qulonglong pubId) const
{
    IDList ret;
    bool ok = true;

    QSqlQuery query(database());
    ok &= query.prepare("SELECT * from publication_author WHERE publicationId = :id");
    query.bindValue(":id", pubId);
    ok &= query.exec();

    debug(query);

    while(ok && query.next()) {
        ret.append(query.record().value("authorId").toULongLong());
    }

    return ret;
}

QSet<qulonglong> SQLitePublicationDAO::toAuthorSet(Author::List authors) const
{
    QSet<qulonglong> ret;

    foreach(Author::Ptr author, authors) {
        ret.insert(author->id());
    }

    return ret;
}
