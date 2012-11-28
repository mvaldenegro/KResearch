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
#include <library/DocumentType.h>
#include <library/Journal.h>

#include <QStringList>
#include <QString>

class Document : public BaseEntity
{
    public:

        //typedef QSharedPointer<Publication> Ptr;
        typedef Document * Ptr;
        typedef QList<Ptr> List;

        Document();
        ~Document();

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

        Journal::Ptr journal() const
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

        bool isPeerReviewed() const
        {
            return mIsPeerReviewed;
        }

        QString publisher() const
        {
            return mPublisher;
        }

        bool isPublished() const
        {
            return mIsPublished;
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

        void setJournal(Journal::Ptr journal)
        {
            this->mJournal = journal;
        }

        void setLocalUrl(QString mLocalURL)
        {
            this->mLocalURL = mLocalURL;
        }

        void setNumber(int mNumber)
        {
            this->mNumber = mNumber;
        }

        void setPeerReviewed(bool peerReview)
        {
            this->mIsPeerReviewed = peerReview;
        }

        void setPublisher(QString mPublisher)
        {
            this->mPublisher = mPublisher;
        }

        void setPublished(bool published)
        {
            this->mIsPublished = published;
        }

        void setTitle(QString mTitle)
        {
            this->mTitle = mTitle;
        }

        void setType(DocumentType type)
        {
            this->mType = type;
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

        QString title() const
        {
            return mTitle;
        }

        DocumentType type() const
        {
            return mType;
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
    QString mPublisher;
    int mVolume;
    int mNumber;
    QString mUrl;
    QString mDoi;
    QString mIsbn;
    QString mLocalURL;
    Author::List mAuthors;

    bool mIsPublished;
    bool mIsPeerReviewed;

    DocumentType mType;
    Journal::Ptr mJournal;
};

#endif /* PUBLICATION_H_ */
