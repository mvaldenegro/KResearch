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

#ifndef SQLITEAUTHORDAO_H_
#define SQLITEAUTHORDAO_H_

#include <library/dao/AuthorDAO.h>
#include <library/sqlite/SQLiteBaseDAO.h>

class SQLiteRepository;

class SQLiteAuthorDAO : public AuthorDAO, public SQLiteBaseDAO
{
    friend class SQLiteRepository;

    public:
        SQLiteAuthorDAO(SQLiteRepository *cache);
        virtual ~SQLiteAuthorDAO();

        virtual Author::Ptr findById(qulonglong id) const;
        virtual Author::Ptr findByFullName(const QString& firstName, const QString& lastName) const;

        virtual bool saveOrUpdate(Author::Ptr author);

        virtual Author::List findAll() const;

        virtual QStringList authorNames() const;

    protected:

        bool save(Author::Ptr author);
        bool update(Author::Ptr author);
};

#endif /* SQLITEAUTHORDAO_H_ */
