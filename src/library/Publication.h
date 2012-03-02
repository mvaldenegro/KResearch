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

#ifndef PUBLICATION_H_
#define PUBLICATION_H_

#include <library/BaseEntity.h>
#include <library/Author.h>

#define QT_SHAREDPOINTER_TRACK_POINTERS
#include <QSharedPointer>
#include <QStringList>
#include <QString>

class Publication : public BaseEntity
{
    public:

        //typedef QSharedPointer<Publication> Ptr;
        typedef Publication * Ptr;
        typedef QList<Ptr> List;

        Publication();
        ~Publication();

        QString abstract() const
        {
            return mAbstract;
        }

        Author::List authors() const
        {
            return mAuthors;
        }

        QStringList authorNames() const
        {
            QStringList ret;

            foreach(Author::Ptr author, authors()) {
                ret += author->fullName();
            }

            return ret;
        }

        QString conference() const
        {
            return mConference;
        }

        QString doi() const
        {
            return mDoi;
        }

        QString isbn() const
        {
            return mIsbn;
        }

        QString journal() const
        {
            return mJournal;
        }

        QString localUrl() const
        {
            return mLocalURL;
        }

        int number() const
        {
            return mNumber;
        }

        QString publisher() const
        {
            return mPublisher;
        }

        QString series() const
        {
            return mSeries;
        }

        void setAbstract(QString mAbstract)
        {
            this->mAbstract = mAbstract;
        }

        void setAuthors(Author::List mAuthors)
        {
            this->mAuthors = mAuthors;
        }

        void setConference(QString mConference)
        {
            this->mConference = mConference;
        }

        void setDoi(QString mDoi)
        {
            this->mDoi = mDoi;
        }

        void setIsbn(QString mIsbn)
        {
            this->mIsbn = mIsbn;
        }

        void setJournal(QString mJournal)
        {
            this->mJournal = mJournal;
        }

        void setLocalUrl(QString mLocalURL)
        {
            this->mLocalURL = mLocalURL;
        }

        void setNumber(int mNumber)
        {
            this->mNumber = mNumber;
        }

        void setPublisher(QString mPublisher)
        {
            this->mPublisher = mPublisher;
        }

        void setSeries(QString mSeries)
        {
            this->mSeries = mSeries;
        }

        void setSubseries(QString mSubseries)
        {
            this->mSubseries = mSubseries;
        }

        void setTitle(QString mTitle)
        {
            this->mTitle = mTitle;
        }

        void setUrl(QString mUrl)
        {
            this->mUrl = mUrl;
        }

        void setVolume(int mVolume)
        {
            this->mVolume = mVolume;
        }

        void setYear(int mYear)
        {
            this->mYear = mYear;
        }

        QString subseries() const
        {
            return mSubseries;
        }

        QString title() const
        {
            return mTitle;
        }

        QString url() const
        {
            return mUrl;
        }

        int volume() const
        {
            return mVolume;
        }

        int year() const
        {
            return mYear;
        }

private:
    QString mTitle;
    QString mAbstract;
    int mYear;
    QString mConference;
    QString mJournal;
    QString mPublisher;
    QString mSeries;
    QString mSubseries;
    int mVolume;
    int mNumber;
    QString mUrl;
    QString mDoi;
    QString mIsbn;
    QString mLocalURL;
    Author::List mAuthors;
};

#endif /* PUBLICATION_H_ */
