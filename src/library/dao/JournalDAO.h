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

#ifndef JOURNALDAO_H_
#define JOURNALDAO_H_

#include <library/dao/BaseDAO.h>
#include <library/Journal.h>

#include <QStringList>

class JournalDAO : public BaseDAO
{
    public:
        JournalDAO();
        virtual ~JournalDAO();

        virtual Journal::Ptr findById(qulonglong id) const = 0;
        virtual Journal::Ptr findByName(const QString& name) const = 0;

        virtual bool saveOrUpdate(Journal::Ptr author) = 0;

        virtual Journal::List findAll() const = 0;

        virtual QStringList journalNames() const = 0;
};

#endif /* JOURNALDAO_H_ */
