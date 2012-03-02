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

#include "SQLiteBaseDAO.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

SQLiteBaseDAO::SQLiteBaseDAO(SQLiteRepository *cache)
 : mObjectCache(cache)
{
}

SQLiteBaseDAO::~SQLiteBaseDAO()
{
}

void SQLiteBaseDAO::debug(const QSqlQuery& query) const
{
    qDebug() << "Executing query:" << lastExecutedQuery(query);

    handleErrors(query);
}

void SQLiteBaseDAO::handleErrors(const QSqlQuery& query) const
{
    QSqlError error = query.lastError();

    if(error.isValid()) {
        qDebug() << "Error executing query:" << error.text();
    }
}

QString SQLiteBaseDAO::lastExecutedQuery(const QSqlQuery& query) const
{
    QString str = query.lastQuery();
    QMap<QString, QVariant> bounds = query.boundValues();

    foreach(QString key, bounds.keys()) {
        str.replace(key, "\"" + bounds.value(key).toString() + "\"");
    }

    return str;
}

qulonglong SQLiteBaseDAO::lastInsertRowID() const
{
    QSqlQuery query("SELECT last_insert_rowid()", repository()->database());
    debug(query);

    if(query.next()) {
        return query.record().value(0).toULongLong();
    }

    return (qulonglong) -1;
}
