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
 * along with Epic Framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SQLITEJOURNALDAO_H_
#define SQLITEJOURNALDAO_H_

#include <library/dao/JournalDAO.h>
#include <library/sqlite/SQLiteBaseDAO.h>

class SQLiteRepository;

class SQLiteJournalDAO : public JournalDAO, public SQLiteBaseDAO
{
    friend class SQLiteRepository;

    public:
        SQLiteJournalDAO(SQLiteRepository *cache);
        virtual ~SQLiteJournalDAO();

        virtual Journal::Ptr findById(qulonglong id) const;
        virtual Journal::Ptr findByName(const QString& name) const;

        virtual bool saveOrUpdate(Journal::Ptr author);

        virtual Journal::List findAll() const;

        virtual QStringList journalNames() const;

    protected:

        bool save(Journal::Ptr journal);
        bool update(Journal::Ptr journal);
};
#endif /* SQLITEJOURNALDAO_H_ */
