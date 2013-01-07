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

#ifndef QUERYEXECUTOR_H_
#define QUERYEXECUTOR_H_

#include <library/sqlite/Transaction.h>

#include <QMap>
#include <QVariant>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlDatabase>


typedef QMap<QString, QVariant> QueryParameters;

inline QueryParameters makeQueryParameters(QString name, QVariant value)
{
    QueryParameters ret;
    ret[name] = value;

    return ret;
}

class QueryExecutor
{
    public:
        QueryExecutor(QSqlDatabase database = QSqlDatabase::database());
        virtual ~QueryExecutor();

        bool insert(const QString& tableName, const QueryParameters& params);
        bool update(const QString& tableName, const QueryParameters& constraints, const QueryParameters& values);

        QSqlQuery select(const QString& tableName, const QStringList columns = QStringList(),
                         const QueryParameters& constraints = QueryParameters());

        bool remove(const QString& tableName, const QueryParameters& params);

        QSqlQuery customQuery(const QString& rawQuery, const QueryParameters& params = QueryParameters());

        QVariant columnValue(const QString& tableName, const QString& column, const QueryParameters& constraints);

        qulonglong lastInsertID();

        inline QSqlDatabase database() const
        {
            return mDatabase;
        }

    private:
        bool executeQuery(const QString& queryString, const QueryParameters& params, QSqlQuery *ret = nullptr);

    private:
        //Transaction mTransaction;
        QSqlDatabase mDatabase;
};

#endif /* QUERYEXECUTOR_H_ */
