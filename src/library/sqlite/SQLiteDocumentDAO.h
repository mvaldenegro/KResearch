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

#ifndef SQLITEPUBLICATIONDAO_H_
#define SQLITEPUBLICATIONDAO_H_

#include <library/dao/DocumentDAO.h>
#include <library/sqlite/SQLiteBaseDAO.h>

class SQLiteRepository;

class SQLiteDocumentDAO : public DocumentDAO, public SQLiteBaseDAO
{
    friend class SQLiteRepository;

    public:
        SQLiteDocumentDAO(SQLiteRepository *cache);
        virtual ~SQLiteDocumentDAO();

        virtual Document::Ptr findById(qulonglong id) const;

        virtual bool saveOrUpdate(Document::Ptr pub);

        virtual Document::List findAll() const;

        virtual QStringList journals() const;
        virtual QStringList conferences() const;

    protected:

        bool save(Document::Ptr pub);
        bool update(Document::Ptr pub);

        bool updateAuthors(Document::Ptr pub);

        IDList authorIDs(qulonglong pubId) const;
        QSet<qulonglong> toAuthorSet(Author::List authors) const;
};

#endif /* SQLITEPUBLICATIONDAO_H_ */
