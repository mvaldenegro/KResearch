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

#include "SQLiteKeywordDAO.h"
#include <library/sqlite/SQLiteRepository.h>
#include <library/sqlite/QueryExecutor.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

SQLiteKeywordDAO::SQLiteKeywordDAO(SQLiteRepository *cache)
: KeywordDAO(), SQLiteBaseDAO(cache)
{
}

SQLiteKeywordDAO::~SQLiteKeywordDAO()
{
}

Keyword::Ptr SQLiteKeywordDAO::findById(qulonglong id) const
{
    if(repository()->keywords()->contains(id)) {
        return repository()->keywords()->find(id);
    }

    QSqlQuery query = QueryExecutor().select("keyword", QStringList(), makeQueryParameters("id", id));

    if(query.next()) {

        QSqlRecord record = query.record();
        Keyword::Ptr keyword = Keyword::Ptr(new Keyword());

        keyword->setId(id);
        keyword->setName(record.value("name").toString());

        repository()->keywords()->insert(id, keyword);

        emit dataChanged();

        return keyword;
    }

    return Keyword::Ptr(0);
}

bool SQLiteKeywordDAO::saveOrUpdate(Keyword::Ptr keyword)
{
    if(!keyword) {
        return false;
    }

    const qulonglong invalidId = (qulonglong) -1;

    if(keyword->id() == invalidId) {

        return save(keyword);
    } else {

        return update(keyword);
    }
}

Keyword::List SQLiteKeywordDAO::findAll() const
{
    return repository()->keywords()->findAll();
}

bool SQLiteKeywordDAO::save(Keyword::Ptr keyword)
{
    if(!keyword) {
        return false;
    }

    QueryExecutor executor;
    QueryParameters params;
    params.insert("name", keyword->name());
    bool ok = executor.insert("keyword", params);

    if(ok) {
        qulonglong id = executor.lastInsertID();
        keyword->setId(id);

        repository()->keywords()->insert(id, keyword);

        emit dataChanged();
    }

    return ok;
}

bool SQLiteKeywordDAO::update(Keyword::Ptr keyword)
{
    if(!keyword) {
        return false;
    }

    QueryParameters params;
    params.insert("name", keyword->name());
    bool ok = QueryExecutor().update("keyword", makeQueryParameters("id", keyword->id()), params);

    emit dataChanged();

    return ok;
}
