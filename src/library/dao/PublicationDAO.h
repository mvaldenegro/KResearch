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

#ifndef PUBLICATIONDAO_H_
#define PUBLICATIONDAO_H_

#include <QStringList>

#include <library/dao/BaseDAO.h>
#include <library/Publication.h>

class PublicationDAO : public BaseDAO
{
    public:
        PublicationDAO();
        virtual ~PublicationDAO();

        virtual Publication::Ptr findById(qulonglong id) const = 0;

        virtual bool saveOrUpdate(Publication::Ptr pub) = 0;

        virtual Publication::List findAll() const = 0;

        virtual QStringList journals() const = 0;
        virtual QStringList conferences() const = 0;
};

#endif /* PUBLICATIONDAO_H_ */
