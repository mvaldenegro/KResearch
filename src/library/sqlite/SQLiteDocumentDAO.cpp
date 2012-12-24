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

#include "SQLiteDocumentDAO.h"
#include <library/sqlite/SQLiteRepository.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

SQLiteDocumentDAO::SQLiteDocumentDAO(SQLiteRepository *cache)
: DocumentDAO(), SQLiteBaseDAO(cache)
{
}

SQLiteDocumentDAO::~SQLiteDocumentDAO()
{
}

Document::Ptr SQLiteDocumentDAO::findById(qulonglong id) const
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
            Document::Ptr pub = Document::Ptr(new Document());

            pub->setId(id);
            pub->setTitle(record.value("title").toString());
            pub->setAbstract(record.value("abstract").toString());
            pub->setYear(record.value("year").toInt());
            pub->setConference(record.value("conference").toString());
            pub->setPublisher(record.value("publisher").toString());
            pub->setVolume(record.value("volume").toInt());
            pub->setNumber(record.value("number").toInt());
            pub->setUrl(record.value("url").toString());
            pub->setDoi(record.value("doi").toString());
            pub->setIsbn(record.value("isbn").toString());
            pub->setLocalUrl(record.value("localURL").toString());
            pub->setType(DocumentType::fromUInt(record.value("type").toUInt()));
            pub->setPublished(record.value("isPublished").toBool());
            pub->setPeerReviewed(record.value("isPeerReviewed").toBool());

            repository()->publications()->insert(id, pub);

            IDList idAuthors = authorIDs(id);
            Author::List authors;

            foreach(qulonglong aid, idAuthors) {
                authors.append(repository()->authorDAO()->findById(aid));
            }

            pub->setAuthors(authors);

            qulonglong jid = record.value("journalId").toULongLong();

            if(jid != 0) {
                pub->setJournal(repository()->journalDAO()->findById(jid));
            }

            emit dataChanged();

            return pub;
        }
    }

    return Document::Ptr();
}

bool SQLiteDocumentDAO::saveOrUpdate(Document::Ptr pub)
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

Document::List SQLiteDocumentDAO::findAll() const
{
    return repository()->publications()->findAll();
}

QStringList SQLiteDocumentDAO::journals() const
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

QStringList SQLiteDocumentDAO::conferences() const
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

bool SQLiteDocumentDAO::remove(Document::Ptr entity)
{
    QSqlQuery query(database());
    query.prepare("DELETE FROM publication WHERE id = :id");
    query.bindValue(":id", entity->id());

    bool ret =  query.exec();

    if(ret) {
        repository()->publications()->remove(entity->id());

        emit dataChanged();
    }

    return ret;
}

bool SQLiteDocumentDAO::save(Document::Ptr pub)
{
    if(!pub) {
        return false;
    }

    bool ok = true;
    //database().transaction();

    QSqlQuery query(database());
    ok &= query.prepare("INSERT INTO publication(title, abstract, year, conference, publisher, "
                                                "volume, number, url, doi, isbn, localURL,"
                                                "type, isPublished, isPeerReviewed, journalId) "
                         "VALUES(:title, :abstract, :year, :conference, :publisher, "
                                ":volume, :number, :url, :doi, :isbn, :localURL, "
                                ":type, :isPublished, :isPeerReviewed, :journalId)");

    query.bindValue(":title", pub->title());
    query.bindValue(":abstract", pub->abstract());
    query.bindValue(":year", pub->year());
    query.bindValue(":conference", pub->conference());
    query.bindValue(":publisher", pub->publisher());
    query.bindValue(":volume", pub->volume());
    query.bindValue(":number", pub->number());
    query.bindValue(":url", pub->url());
    query.bindValue(":doi", pub->doi());
    query.bindValue(":isbn", pub->isbn());
    query.bindValue(":localURL", pub->localUrl());
    query.bindValue(":type", pub->type().toUInt());
    query.bindValue(":isPublished", pub->isPublished());
    query.bindValue(":isPeerReviewed", pub->isPeerReviewed());

    if(pub->journal()) {
        query.bindValue(":journalId", pub->journal()->id());
    } else {
        query.bindValue(":journalId", QVariant());
    }

    ok &= query.exec();

    debug(query);

    if(ok) {
        qulonglong id = lastInsertRowID();
        pub->setId(id);

        updateAuthors(pub);

        repository()->journalDAO()->saveOrUpdate(pub->journal());
        repository()->publications()->insert(id, pub);
    }

    if(!ok) {
        //ok &= database().rollback();
    } else {
        //ok &= database().commit();
    }

    emit dataChanged();

    return ok;
}

bool SQLiteDocumentDAO::update(Document::Ptr pub)
{
    if(!pub) {
        return false;
    }

    repository()->journalDAO()->saveOrUpdate(pub->journal());

    bool ok = true;

    QSqlQuery query(database());
    ok &= query.prepare("UPDATE publication SET title = :title, abstract = :abstract, year = :year, conference = :conference,"
                        " publisher = :publisher, volume = :volume, number = :number, url = :url, "
                        " doi = :doi, isbn = :isbn, localURL = :localURL, type = :type, isPublished = :isPublished,"
                        " isPeerReviewed = :isPeerReviewed, journalId = :journalId WHERE id = :id");

    query.bindValue(":id", pub->id());
    query.bindValue(":title", pub->title());
    query.bindValue(":abstract", pub->abstract());
    query.bindValue(":year", pub->year());
    query.bindValue(":conference", pub->conference());
    query.bindValue(":publisher", pub->publisher());
    query.bindValue(":volume", pub->volume());
    query.bindValue(":number", pub->number());
    query.bindValue(":url", pub->url());
    query.bindValue(":doi", pub->doi());
    query.bindValue(":isbn", pub->isbn());
    query.bindValue(":localURL", pub->localUrl());
    query.bindValue(":type", pub->type().toUInt());
    query.bindValue(":isPublished", pub->isPublished());
    query.bindValue(":isPeerReviewed", pub->isPeerReviewed());

    if(pub->journal()) {
        query.bindValue(":journalId", pub->journal()->id());
    } else {
        query.bindValue(":journalId", QVariant());
    }

    ok &= query.exec();

    debug(query);

    updateAuthors(pub);

    emit dataChanged();

    return ok;
}

bool SQLiteDocumentDAO::updateAuthors(Document::Ptr pub)
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

IDList SQLiteDocumentDAO::authorIDs(qulonglong pubId) const
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

QSet<qulonglong> SQLiteDocumentDAO::toAuthorSet(Author::List authors) const
{
    QSet<qulonglong> ret;

    foreach(Author::Ptr author, authors) {
        ret.insert(author->id());
    }

    return ret;
}
