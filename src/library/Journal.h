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

#ifndef JOURNAL_H_
#define JOURNAL_H_

#include <library/BaseEntity.h>
#include <library/JournalPolicy.h>

#include <QList>

class Journal : public BaseEntity
{
    public:

        typedef Journal *Ptr;
        typedef QList<Ptr> List;

        Journal();
        ~Journal();

        JournalPolicy journalPolicy() const
        {
            return mJournalPolicy;
        }

        QString name() const
        {
            return mName;
        }

        int publicationCount() const
        {
            return mPublicationCount;
        }

        QString publisher() const
        {
            return mPublisher;
        }

        void setJournalPolicy(JournalPolicy mJournalPolicy)
        {
            this->mJournalPolicy = mJournalPolicy;
        }

        void setName(QString mName)
        {
            this->mName = mName;
        }

        void setPublicationCount(int mPublicationCount)
        {
            this->mPublicationCount = mPublicationCount;
        }

        void setPublisher(QString mPublisher)
        {
            this->mPublisher = mPublisher;
        }

        void setUrl(QString mURL)
        {
            this->mURL = mURL;
        }

        QString url() const
        {
            return mURL;
        }

private:
    QString mName;
    QString mPublisher;
    QString mURL;
    int mPublicationCount;
    JournalPolicy mJournalPolicy;
};

#endif /* JOURNAL_H_ */
