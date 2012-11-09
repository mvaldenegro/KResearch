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

#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <QSharedPointer>

#include <library/Author.h>
#include <library/Publication.h>
#include <library/Journal.h>

#include <library/dao/AuthorDAO.h>
#include <library/dao/PublicationDAO.h>
#include <library/dao/JournalDAO.h>

#include <library/RepositoryCache.h>

class Repository
{
    public:
        Repository();
        virtual ~Repository();

        virtual AuthorDAO * authorDAO() const = 0;
        virtual PublicationDAO * publicationDAO() const = 0;
        virtual JournalDAO * journalDAO() const = 0;

        virtual void populate() = 0;

        RepositoryCache<Author>* authors()
        {
            return mAuthorCache;
        }

        RepositoryCache<Publication>* publications()
        {
            return mPubCache;
        }

        RepositoryCache<Journal> *journals()
        {
            return mJournalCache;
        }

        static Repository *self()
        {
            return mInstance;
        }

    private:

        static Repository *mInstance;

        RepositoryCache<Author> *mAuthorCache;
        RepositoryCache<Publication> *mPubCache;
        RepositoryCache<Journal> *mJournalCache;
};

#endif /* REPOSITORY_H_ */
