/*
 * Copyright (C) 2011-2012 Matias Valdenegro <matias.valdenegro@gmail.com>
 * This file is part of kresearch.
 *
 * kresearch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * kresearch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with kresearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SQLiteAuthorDAO.h"
#include <sqliteLibrary/SQLiteRepository.h>

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

    QSqlQuery query(database());
    bool ok = true;
    ok &= query.prepare("SELECT * FROM author WHERE id = :id");
    query.bindValue(":id", id);
    ok &= query.exec();

    debug(query);

    if(ok) {

        if(query.next()) {

            QSqlRecord record = query.record();
            qulonglong id = record.value("id").toULongLong();
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

    }

    return Author::Ptr();
}

Author::Ptr SQLiteAuthorDAO::findByFullName(const QString& firstName, const QString& lastName) const
{
    QSqlQuery query(database());
    bool ok = true;
    ok &= query.prepare("SELECT id FROM author WHERE firstName = :firstName AND lastName = :lastName");
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    ok &= query.exec();

    debug(query);

    if(ok && query.next()) {
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

    bool ok = true;
    database().transaction();

    qDebug() << "Transaciton ok?" << ok;

    QSqlQuery query(database());
    ok &= query.prepare("INSERT INTO author(firstName, lastName, emailAddress, affiliation) "
                        "VALUES(:firstName, :lastName, :emailAddress, :affiliation)");

    qDebug() << "Prepare ok?" << ok;

    query.bindValue(":firstName", author->firstName());
    query.bindValue(":lastName", author->lastName());
    query.bindValue(":emailAddress", author->emailAddress());
    query.bindValue(":affiliation", author->affiliation());
    ok &= query.exec();

    qDebug() << "Query ok?" << ok;

    debug(query);

    if(ok) {
        qulonglong id = lastInsertRowID();
        author->setId(id);

        repository()->authors()->insert(id, author);
    } else {
        qDebug() << "Query failed!?";
    }

    if(!ok) {
        ok &= database().rollback();
    } else {
        ok &= database().commit();
    }

    emit dataChanged();

    return ok;
}

bool SQLiteAuthorDAO::update(Author::Ptr author)
{
    if(!author) {
        return false;
    }

    bool ok = true;

    QSqlQuery query(database());
    ok &= query.prepare("UPDATE author SET firstName = :firstName, lastName = :lastName, emailAddress = :emailAddress,"
                        " affiliation = :affiliation "
                        "WHERE id = :id");

    query.bindValue(":id", author->id());
    query.bindValue(":firstName", author->firstName());
    query.bindValue(":lastName", author->lastName());
    query.bindValue(":emailAddress", author->emailAddress());
    query.bindValue(":affiliation", author->affiliation());
    ok &= query.exec();

    debug(query);

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
