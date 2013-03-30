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

#ifndef SQLITEOBJECTCACHE_H_
#define SQLITEOBJECTCACHE_H_

#include <QSqlDatabase>
#define QT_SHAREDPOINTER_TRACK_POINTERS
#include <QSharedPointer>
#include <QMap>

#include <library/Author.h>
#include <library/Document.h>

#include <library/dao/AuthorDAO.h>
#include <library/dao/DocumentDAO.h>

#include <library/Repository.h>

class SQLiteRepository : public Repository
{
    public:
        SQLiteRepository(QSqlDatabase db);
        virtual ~SQLiteRepository();

        AuthorDAO * authorDAO() const
        {
            return mAuthorDAO;
        }

        DocumentDAO * publicationDAO() const
        {
            return mPublicationDAO;
        }

        JournalDAO * journalDAO() const
        {
            return mJournalDAO;
        }

        KeywordDAO * keywordDAO() const
        {
            return mKeywordDAO;
        }

        DocumentCollectionDAO * collectionDAO() const
        {
            return mCollectionDAO;
        }

        QSqlDatabase database()
        {
            return mDB;
        }

        void populate();

    private:
        QSqlDatabase mDB;

        AuthorDAO *mAuthorDAO;
        DocumentDAO *mPublicationDAO;
        JournalDAO *mJournalDAO;
        KeywordDAO *mKeywordDAO;
        DocumentCollectionDAO *mCollectionDAO;
};

#endif /* SQLITEOBJECTCACHE_H_ */
