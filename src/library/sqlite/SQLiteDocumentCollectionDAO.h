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

#ifndef SQLITEDOCUMENTCOLLECTIONDAO_H_
#define SQLITEDOCUMENTCOLLECTIONDAO_H_

#include <library/dao/DocumentCollectionDAO.h>
#include <library/sqlite/SQLiteBaseDAO.h>

class SQLiteRepository;

class SQLiteDocumentCollectionDAO : public DocumentCollectionDAO, public SQLiteBaseDAO
{
    public:
        SQLiteDocumentCollectionDAO(SQLiteRepository *cache);
        virtual ~SQLiteDocumentCollectionDAO();

        virtual DocumentCollection::Ptr findById(qulonglong id) const;

        virtual bool saveOrUpdate(DocumentCollection::Ptr pub);

        virtual DocumentCollection::List findAll() const;
        virtual DocumentCollection::Ptr findByName(const QString& name) const;

    private:
        bool save(DocumentCollection::Ptr pub);
        bool update(DocumentCollection::Ptr pub);


};


#endif /* SQLITEDOCUMENTCOLLECTIONDAO_H_ */
