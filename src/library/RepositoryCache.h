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

#ifndef REPOSITORYCACHE_H_
#define REPOSITORYCACHE_H_

#include <QDebug>
#include <QMap>
#include <QList>

template<typename T>
class RepositoryCache
{
    public:
        RepositoryCache()
        {
        }

        ~RepositoryCache()
        {
        }

        bool contains(qulonglong id) const
        {
            return mCacheMap.contains(id);
        }

        void insert(qulonglong id, typename T::Ptr value)
        {
            mCacheMap.insert(id, value);
            mCacheList.append(value);
        }

        typename T::Ptr find(qulonglong id)
        {
            if(contains(id)) {
                return mCacheMap.value(id);
            }

            return typename T::Ptr();
        }

        typename T::List findAll()
        {
            return mCacheList;
        }

    private:
        QList<typename T::Ptr> mCacheList;
        QMap<qulonglong, typename T::Ptr> mCacheMap;
};


#endif /* REPOSITORYCACHE_H_ */
