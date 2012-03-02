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

#ifndef SQLITEBASEDAO_H_
#define SQLITEBASEDAO_H_

#include <QSqlQuery>

#include <sqliteLibrary/SQLiteRepository.h>

class SQLiteBaseDAO
{
    public:
        SQLiteBaseDAO(SQLiteRepository *cache);
        virtual ~SQLiteBaseDAO();

        void debug(const QSqlQuery &query) const;
        void handleErrors(const QSqlQuery &query) const;

        QString lastExecutedQuery(const QSqlQuery& query) const;

        qulonglong lastInsertRowID() const;

        inline SQLiteRepository *repository() const
        {
            return mObjectCache;
        }

    protected:
        inline QSqlDatabase database() const
        {
            return repository()->database();
        }

        bool transaction() const;
        bool commit() const;
        bool rollback() const;

    private:
        SQLiteRepository *mObjectCache;
};

#endif /* SQLITEBASEDAO_H_ */
