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

#ifndef GENERICDAO_H_
#define GENERICDAO_H_

#include <QList>
#include <qglobal.h>

template<typename T>
class GenericDAO
{
    public:

        GenericDAO()
        {
        }

        virtual ~GenericDAO()
        {
        }

        virtual typename T::Ptr findById(qulonglong id) const = 0;

        virtual typename T::List findByIds(QList<qulonglong> ids) const
        {
            typename T::List ret;

            for(qulonglong id : ids) {
                ret.append(findById(id));
            }

            return ret;
        }

        virtual bool saveOrUpdate(typename T::Ptr entity) = 0;

        virtual typename T::List findAll() const = 0;

        virtual bool remove(typename T::Ptr entity)
        {
            return false;
        }

        virtual void beginTransaction()
        {
        }

        virtual void endTransaction()
        {
        }

};


#endif /* GENERICDAO_H_ */
