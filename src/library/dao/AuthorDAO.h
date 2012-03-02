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

#ifndef AUTHORDAO_H_
#define AUTHORDAO_H_

#include <library/dao/BaseDAO.h>
#include <library/Author.h>

#include <QStringList>

class AuthorDAO : public BaseDAO
{
    public:
        AuthorDAO();
        virtual ~AuthorDAO();

        virtual Author::Ptr findById(qulonglong id) const = 0;
        virtual Author::Ptr findByFullName(const QString& firstName, const QString& lastName) const = 0;

        virtual bool saveOrUpdate(Author::Ptr author) = 0;

        virtual Author::List findAll() const = 0;

        virtual QStringList authorNames() const = 0;
};

#endif /* AUTHORDAO_H_ */
