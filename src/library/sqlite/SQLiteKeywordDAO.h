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

#ifndef SQLITEKEYWORDDAO_H_
#define SQLITEKEYWORDDAO_H_

#include <library/dao/KeywordDAO.h>
#include <library/sqlite/SQLiteBaseDAO.h>

class SQLiteRepository;

class SQLiteKeywordDAO : public KeywordDAO, public SQLiteBaseDAO
{
    public:
        SQLiteKeywordDAO(SQLiteRepository *cache);
        virtual ~SQLiteKeywordDAO();

        virtual Keyword::Ptr findById(qulonglong id) const;

        virtual bool saveOrUpdate(Keyword::Ptr pub);

        virtual Keyword::List findAll() const;

    private:
        bool save(Keyword::Ptr pub);
        bool update(Keyword::Ptr pub);


};

#endif /* SQLITEKEYWORDDAO_H_ */
