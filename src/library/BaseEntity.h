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

#ifndef BASEENTITY_H_
#define BASEENTITY_H_

#include <QObject>
#include <QSharedPointer>
#include <QStringList>
#include <QList>

typedef QList<qulonglong> IDList;

class BaseEntity
{
    public:
        BaseEntity();
        ~BaseEntity();

        qulonglong id() const
        {
            return mID;
        }

        void setId(qulonglong id)
        {
            mID = id;
        }

        bool equals(const BaseEntity& other) const;
        bool equals(const QSharedPointer<BaseEntity>& other) const;

        template<typename T>
        inline static QString serializeEntityIDs(typename T::List entities)
        {
            QStringList ret;

            for(typename T::Ptr entity: entities) {
                ret += QString::number(entity->id());
            }

            return ret.join(",");
        }


    private:
        qulonglong mID;
};

#endif /* BASEENTITY_H_ */
