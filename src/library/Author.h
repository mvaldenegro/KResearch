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

#ifndef AUTHOR_H_
#define AUTHOR_H_

#include <library/BaseEntity.h>

#define QT_SHAREDPOINTER_TRACK_POINTERS
#include <QSharedPointer>
#include <QList>

class Author : public BaseEntity
{
    public:

        //typedef QSharedPointer<Author> Ptr;
        typedef Author * Ptr;
        typedef QList<Ptr> List;

        Author();
        ~Author();

        QString fullName() const
        {
            return firstName() + " " + lastName();
        }

        QString editableFullName() const
        {
            return lastName() + ", " + firstName();
        }

        QString affiliation() const
        {
            return mAffiliation;
        }

        QString emailAddress() const
        {
            return mEmailAddress;
        }

        QString firstName() const
        {
            return mFirstName;
        }

        QString lastName() const
        {
            return mLastName;
        }

        void setAffiliation(QString mAffiliation)
        {
            this->mAffiliation = mAffiliation;
        }

        void setEmailAddress(QString mEmailAddress)
        {
            this->mEmailAddress = mEmailAddress;
        }

        void setFirstName(QString mFirstName)
        {
            this->mFirstName = mFirstName;
        }

        void setLastName(QString mLastName)
        {
            this->mLastName = mLastName;
        }

    private:
        QString mFirstName;
        QString mLastName;
        QString mEmailAddress;
        QString mAffiliation;
};

#endif /* AUTHOR_H_ */
