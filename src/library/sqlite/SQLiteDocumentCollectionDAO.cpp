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

#include "SQLiteDocumentCollectionDAO.h"
#include <library/sqlite/SQLiteRepository.h>
#include <library/sqlite/QueryExecutor.h>
#include <util/SerializationUtils.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

SQLiteDocumentCollectionDAO::SQLiteDocumentCollectionDAO(SQLiteRepository *cache)
: DocumentCollectionDAO(), SQLiteBaseDAO(cache)
{
}

SQLiteDocumentCollectionDAO::~SQLiteDocumentCollectionDAO()
{
}

DocumentCollection::Ptr SQLiteDocumentCollectionDAO::findById(qulonglong id) const
{
    if(repository()->collections()->contains(id)) {
        return repository()->collections()->find(id);
    }

    QSqlQuery query = QueryExecutor().select("collection", QStringList(), makeQueryParameters("id", id));

    if(query.next()) {

        QSqlRecord record = query.record();
        DocumentCollection::Ptr collection = DocumentCollection::Ptr(new DocumentCollection());

        collection->setId(id);
        collection->setName(record.value("name").toString());

        IDList documents = SerializationUtils::deserializeListULongLong(record.value("documents").toString());

        collection->setDocuments(Repository::self()->publicationDAO()->findByIds(documents));

        repository()->collections()->insert(id, collection);

        emit dataChanged();

        return collection;
    }

    return DocumentCollection::Ptr(0);
}

bool SQLiteDocumentCollectionDAO::saveOrUpdate(DocumentCollection::Ptr collection)
{
    if(!collection) {
        return false;
    }

    const qulonglong invalidId = (qulonglong) -1;

    if(collection->id() == invalidId) {

        return save(collection);
    } else {

        return update(collection);
    }
}

DocumentCollection::List SQLiteDocumentCollectionDAO::findAll() const
{
    return repository()->collections()->findAll();
}

bool SQLiteDocumentCollectionDAO::save(DocumentCollection::Ptr collection)
{
    if(!collection) {
        return false;
    }

    QueryExecutor executor;
    QueryParameters params;
    params.insert("name", collection->name());
    params.insert("documents", BaseEntity::serializeEntityIDs<Document>(collection->documents()));
    bool ok = executor.insert("collection", params);

    if(ok) {
        qulonglong id = executor.lastInsertID();
        collection->setId(id);

        repository()->collections()->insert(id, collection);

        emit dataChanged();
    }

    return ok;
}

bool SQLiteDocumentCollectionDAO::update(DocumentCollection::Ptr collection)
{
    if(!collection) {
        return false;
    }

    QueryParameters params;
    params.insert("name", collection->name());
    params.insert("documents", BaseEntity::serializeEntityIDs<Document>(collection->documents()));
    bool ok = QueryExecutor().update("collection", makeQueryParameters("id", collection->id()), params);

    emit dataChanged();

    return ok;
}

DocumentCollection::Ptr SQLiteDocumentCollectionDAO::findByName(const QString& name) const
{
    QVariant id = QueryExecutor().columnValue("collection", "id", makeQueryParameters("name", name));

    if(id.isValid() && id.canConvert(QVariant::ULongLong)) {
        return findById(id.toULongLong());
    }

    return DocumentCollection::Ptr(0);
}
