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
#include <library/sqlite/Transaction.h>
#include <library/sqlite/QueryExecutor.h>

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

    QueryExecutor executor(database());
    QSqlQuery query = executor.select("publication", QStringList(), makeQueryParameters("id", id));

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
    if(!entity) {
        return false;
    }

    bool ret = QueryExecutor(database()).remove("publication", makeQueryParameters("id", entity->id()));

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

    QueryExecutor executor(database());
    QueryParameters params;

    params.insert("title", pub->title());
    params.insert("abstract", pub->abstract());
    params.insert("year", pub->year());
    params.insert("conference", pub->conference());
    params.insert("publisher", pub->publisher());
    params.insert("volume", pub->volume());
    params.insert("number", pub->number());
    params.insert("url", pub->url());
    params.insert("doi", pub->doi());
    params.insert("isbn", pub->isbn());
    params.insert("localURL", pub->localUrl());
    params.insert("type", pub->type().toUInt());
    params.insert("isPublished", pub->isPublished());
    params.insert("isPeerReviewed", pub->isPeerReviewed());

    if(pub->journal()) {
        params.insert("journalId", pub->journal()->id());
    } else {
        params.insert("journalId", QVariant());
    }

    bool ok = executor.insert("publication", params);

    if(ok) {
        qulonglong id = executor.lastInsertID();
        pub->setId(id);

        updateAuthors(pub);

        repository()->journalDAO()->saveOrUpdate(pub->journal());
        repository()->publications()->insert(id, pub);

        emit dataChanged();
    }

    return ok;
}

bool SQLiteDocumentDAO::update(Document::Ptr pub)
{
    if(!pub) {
        return false;
    }

    repository()->journalDAO()->saveOrUpdate(pub->journal());

    QueryParameters params;

    params.insert("title", pub->title());
    params.insert("abstract", pub->abstract());
    params.insert("year", pub->year());
    params.insert("conference", pub->conference());
    params.insert("publisher", pub->publisher());
    params.insert("volume", pub->volume());
    params.insert("number", pub->number());
    params.insert("url", pub->url());
    params.insert("doi", pub->doi());
    params.insert("isbn", pub->isbn());
    params.insert("localURL", pub->localUrl());
    params.insert("type", pub->type().toUInt());
    params.insert("isPublished", pub->isPublished());
    params.insert("isPeerReviewed", pub->isPeerReviewed());

    if(pub->journal()) {
        params.insert("journalId", pub->journal()->id());
    } else {
        params.insert("journalId", QVariant());
    }

    bool ok = QueryExecutor().update("publication", makeQueryParameters("id", pub->id()), params);

    if(ok) {
        updateAuthors(pub);

        emit dataChanged();
    }

    return ok;
}

bool SQLiteDocumentDAO::updateAuthors(Document::Ptr pub)
{
    foreach(Author::Ptr author, pub->authors()) {
        repository()->authorDAO()->saveOrUpdate(author);
    }

    QSet<qulonglong> updatedAuthorIDs = toAuthorSet(pub->authors());
    QSet<qulonglong> storedAuthorIDs = authorIDs(pub->id()).toSet();

    qDebug() << "updatedAuthors" << updatedAuthorIDs;
    qDebug() << "storedAuthors" << storedAuthorIDs;

    qDebug() << "Added authors" << updatedAuthorIDs - storedAuthorIDs;
    qDebug() << "Removed authors" << storedAuthorIDs - updatedAuthorIDs;

    QueryExecutor executor;

    if(updatedAuthorIDs != storedAuthorIDs) {

        executor.remove("publication_author", makeQueryParameters("publicationId", pub->id()));

        foreach(qulonglong aid, updatedAuthorIDs) {

            QueryParameters params;
            params.insert("publicationId", pub->id());
            params.insert("authorId", aid);
            executor.insert("publication_author", params);
        }
    }

    return true;
}

IDList SQLiteDocumentDAO::authorIDs(qulonglong pubId) const
{
    IDList ret;
    QSqlQuery query = QueryExecutor().select("publication_author", QStringList(),
                                             makeQueryParameters("publicationId", pubId));

    while(query.next()) {
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
