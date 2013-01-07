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

#include "SQLiteAuthorDAO.h"
#include <library/sqlite/SQLiteRepository.h>
#include <library/sqlite/QueryExecutor.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

SQLiteAuthorDAO::SQLiteAuthorDAO(SQLiteRepository *cache)
: AuthorDAO(), SQLiteBaseDAO(cache)
{
}

SQLiteAuthorDAO::~SQLiteAuthorDAO()
{
}

Author::Ptr SQLiteAuthorDAO::findById(qulonglong id) const
{
    if(repository()->authors()->contains(id)) {
        return repository()->authors()->find(id);
    }

    QSqlQuery query = QueryExecutor().select("author", QStringList(), makeQueryParameters("id", id));

    if(query.next()) {

        QSqlRecord record = query.record();
        Author::Ptr author = Author::Ptr(new Author());

        author->setId(id);
        author->setFirstName(record.value("firstName").toString());
        author->setLastName(record.value("lastName").toString());
        author->setEmailAddress(record.value("emailAddress").toString());
        author->setAffiliation(record.value("affiliation").toString());

        repository()->authors()->insert(id, author);

        emit dataChanged();

        return author;
    }

    return Author::Ptr(0);
}

Author::Ptr SQLiteAuthorDAO::findByFullName(const QString& firstName, const QString& lastName) const
{
    QueryParameters params;
    params.insert("firstName", firstName);
    params.insert("lastName", lastName);
    QSqlQuery query = QueryExecutor().select("author", QStringList() << "id", params);

    if(query.next()) {
        return findById(query.record().value("id").toULongLong());
    }

    return Author::Ptr(0);
}

bool SQLiteAuthorDAO::saveOrUpdate(Author::Ptr author)
{
    if(!author) {
        return false;
    }

    const qulonglong invalidId = (qulonglong) -1;

    if(author->id() == invalidId) {

        return save(author);
    } else {

        return update(author);
    }
}

Author::List SQLiteAuthorDAO::findAll() const
{
    return repository()->authors()->findAll();
}

bool SQLiteAuthorDAO::save(Author::Ptr author)
{
    if(!author) {
        return false;
    }

    QueryExecutor executor;
    QueryParameters params;
    params.insert("firstName", author->firstName());
    params.insert("lastName", author->lastName());
    params.insert("emailAddress", author->emailAddress());
    params.insert("affiliation", author->affiliation());
    bool ok = executor.insert("author", params);

    if(ok) {
        qulonglong id = executor.lastInsertID();
        author->setId(id);

        repository()->authors()->insert(id, author);

        emit dataChanged();
    }

    return ok;
}

bool SQLiteAuthorDAO::update(Author::Ptr author)
{
    if(!author) {
        return false;
    }

    QueryParameters params;
    params.insert("firstName", author->firstName());
    params.insert("lastName", author->lastName());
    params.insert("emailAddress", author->emailAddress());
    params.insert("affiliation", author->affiliation());
    bool ok = QueryExecutor().update("author", makeQueryParameters("id", author->id()), params);

    emit dataChanged();

    return ok;
}

QStringList SQLiteAuthorDAO::authorNames() const
{
    QStringList ret;
    Author::List authors = findAll();

    foreach(Author::Ptr author, authors) {
        ret += (author->lastName() + ", " + author->firstName());
    }

    return ret;
}
