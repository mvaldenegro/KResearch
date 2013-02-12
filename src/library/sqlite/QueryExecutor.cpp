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

#include "QueryExecutor.h"

#include <QDebug>
#include <QSqlRecord>

QueryExecutor::QueryExecutor(QSqlDatabase database)
: mDatabase(database)
{
}

QueryExecutor::~QueryExecutor()
{
}

inline QString placeholder(const QString& str)
{
    return ":" + str;
}

inline QStringList makePlaceholders(const QStringList& keys)
{
    QStringList ret;

    for(QString str: keys) {
        ret.append(placeholder(str));
    }

    return ret;
}

bool QueryExecutor::insert(const QString& tableName, const QueryParameters& params)
{
    //TODO: Do some escaping to protect against SQL injections.
    QStringList keys = QStringList(params.keys());
    QStringList placeholders = makePlaceholders(keys);

    QString query = QString("INSERT INTO %1(%2) VALUES(%3)").arg(tableName)
                    .arg(keys.join(", ")).arg(placeholders.join(", "));

    return executeQuery(query, params);
}

inline QString makeWhereConstraint(const QStringList& keys)
{
    QStringList ret;

    for(QString str: keys) {
        ret.append(str + " = " + placeholder(str));
    }

    return ret.join(" AND ");
}

inline QString makeUpdate(const QStringList& keys)
{
    QStringList ret;

    for(QString str: keys) {
        ret.append(str + " = " + placeholder(str));
    }

    return ret.join(", ");
}

bool QueryExecutor::update(const QString& tableName, const QueryParameters& constraints, const QueryParameters& values)
{
    QString where = makeWhereConstraint(constraints.keys());
    QString updt  = makeUpdate(values.keys());
    QString query = QString("UPDATE %1 SET %2 WHERE %3").arg(tableName).arg(updt).arg(where);

    QueryParameters params = values;
    params = params.unite(constraints);

    return executeQuery(query, params);
}
QSqlQuery QueryExecutor::select(const QString& tableName, const QStringList columns, const QueryParameters& constraints)
{
    QString cols = columns.count() > 0 ? columns.join(",") : QString("*");
    QString query = QString("SELECT %1 FROM %2 WHERE %3").arg(cols)
                    .arg(tableName).arg(makeWhereConstraint(constraints.keys()));
    QSqlQuery ret;

    executeQuery(query, constraints, &ret);

    return ret;
}

bool QueryExecutor::remove(const QString& tableName, const QueryParameters& params)
{
    QString query = QString("DELETE FROM %1 WHERE %2").arg(tableName).arg(makeWhereConstraint(params.keys()));

    return executeQuery(query, params);
}

QSqlQuery QueryExecutor::customQuery(const QString& rawQuery, const QueryParameters& params)
{
    QSqlQuery ret;
    executeQuery(rawQuery, params, &ret);

    return ret;
}

QVariant QueryExecutor::columnValue(const QString& tableName, const QString& column, const QueryParameters& constraints)
{
    QSqlQuery query = select(tableName, QStringList() << column, constraints);

    if(query.next()) {
        query.record().value(0);
    }

    return QVariant();
}

qulonglong QueryExecutor::lastInsertID()
{
    QSqlQuery query = customQuery("SELECT last_insert_rowid()");

    if(query.next()) {
        return query.record().value(0).toULongLong();
    }

    return (qulonglong) -1;
}

IDList QueryExecutor::queryOneToManyRelation(const QString& oneTableName, const QString& manyTableName, qulonglong id)
{
    IDList ret;
    QString interTable = oneTableName + QString("_") + manyTableName;
    QString oneColumn = oneTableName + QString("Id");
    QString manyColumn = manyTableName + QString("Id");

    QSqlQuery query = select(interTable, QStringList(), makeQueryParameters(oneColumn, id));


    while(query.next()) {
        ret.append(query.record().value(manyColumn).toULongLong());
    }

    return ret;
}

bool QueryExecutor::executeQuery(const QString& queryString, const QueryParameters& params, QSqlQuery *ret)
{
    QSqlQuery query(database());
    bool success = true;

    success &= query.prepare(queryString);

    for(QString key: params.keys()) {
        query.bindValue(placeholder(key), params.value(key));
    }

    qDebug() << "Executing query:" << queryString;

    success &= query.exec();

    if(success && (ret != nullptr)) {
        *ret = query;
    }

    if(success) {
        qDebug() << "Query successful";
    } else {
        qDebug() << "Query FAILED";
    }

    return success;
}
