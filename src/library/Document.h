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
#include <library/DocumentType.h>
#include <library/Journal.h>

#include <util/NameUtils.h>

#include <QStringList>
#include <QString>

/*! Representation of a range of pages in a book, article, etc.
 */

class PageRange
{
    public:
        PageRange();
        ~PageRange();

        /*! Ending page of this range.
         */

        int pageEnd() const
        {
            return mPageEnd;
        }

        void setPageEnd(int pageEnd)
        {
            mPageEnd = pageEnd;
        }

        /*! Starting page of this range.
         */

        int pageStart() const
        {
            return mPageStart;
        }

        void setPageStart(int pageStart)
        {
            mPageStart = pageStart;
        }

        /*! Converts this instance into a String, which consists of both start and ending pages
         *  separated with a semicolon.
         */
        QString toString();

        /*! Parses a String into PageRange instance. The format is the same as toString().
         */
        static PageRange fromString(const QString& str);

    private:
        int mPageStart;
        int mPageEnd;
};

/*! Document representation.
 *
 * A Document can be any type of document handled by this application, like a research paper/article, a book,
 * a conference paper published in proceedings, a Bachelor/Master/Doctoral thesis, etc.
 *
 * This class contains fields common to many types of documents, for the sake of generality. Each document has a type
 * that defines how the fields should be interpreted.
 *
 */

class Document : public BaseEntity
{
    public:

        //typedef QSharedPointer<Publication> Ptr;
        typedef Document * Ptr;
        typedef QList<Ptr> List;

        Document();
        Document(const Document& copy);
        ~Document();

        /*! Abstract of the document.
         */

        QString abstract() const
        {
            return mAbstract;
        }

        void setAbstract(QString mAbstract)
        {
            this->mAbstract = mAbstract;
        }

        /*! The list of authors of the document. In case the documents contains both authors and editors, the editors
         *  can be stored in the editors field.
         */

        QStringList authors() const
        {
            return mAuthors;
        }

        void setAuthors(QStringList mAuthors)
        {
            this->mAuthors = mAuthors;
        }

        QString shortAuthors() const
        {
            if(authors().count() > 1) {
                return NameUtils::lastName(authors().at(0)) + QString(" et al.");
            } else if(authors().count() > 0) {
                return authors().at(0);
            }

            return QString("Unknown");
        }

        QString longAuthors() const
        {
            return authors().join(", ");
        }

        /*! Name of the conference where this document was published.
         * Can be the name of the conference proceedings.
         */

        QString conference() const
        {
            return mConference;
        }

        void setConference(QString mConference)
        {
            this->mConference = mConference;
        }


        /*! Digital Object Identifier (DOI) of this document.
         */

        QString doi() const
        {
            return mDoi;
        }

        void setDoi(QString mDoi)
        {
            this->mDoi = mDoi;
        }

        /*! International Standard Book Number (ISBN) of this document.
         * ISBN is usually used for books and magazines.
         */

        QString isbn() const
        {
            return mIsbn;
        }

        void setIsbn(QString mIsbn)
        {
            this->mIsbn = mIsbn;
        }

        /*! Pointer to the journal instance where this document was published.
         */

        Journal::Ptr journal() const
        {
            return mJournal;
        }

        void setJournal(Journal::Ptr journal)
        {
            this->mJournal = journal;
        }

        /*! URL to a local file containing this document.
         */

        QString localUrl() const
        {
            return mLocalURL;
        }

        void setLocalUrl(QString mLocalURL)
        {
            this->mLocalURL = mLocalURL;
        }

        /*! Issue number associated with this document, from a magazine or journal.
         */

        int number() const
        {
            return mNumber;
        }

        void setNumber(int mNumber)
        {
            this->mNumber = mNumber;
        }

        /*! Whatever this document was peer-reviewed.
         */

        bool isPeerReviewed() const
        {
            return mIsPeerReviewed;
        }

        void setPeerReviewed(bool peerReview)
        {
            this->mIsPeerReviewed = peerReview;
        }

        /*! Publisher of this document.
         */

        QString publisher() const
        {
            return mPublisher;
        }

        void setPublisher(QString mPublisher)
        {
            this->mPublisher = mPublisher;
        }

        /*! Whatever this document is formally published.
         */

        bool isPublished() const
        {
            return mIsPublished;
        }


        void setPublished(bool published)
        {
            this->mIsPublished = published;
        }

        /*! Title of this document.
         */

        QString title() const
        {
            return mTitle;
        }

        void setTitle(QString mTitle)
        {
            this->mTitle = mTitle;
        }

        /*! Type of this document.
         */

        DocumentType type() const
        {
            return mType;
        }

        void setType(DocumentType type)
        {
            this->mType = type;
        }

        /*! URL of this document, where a copy of the document can be downloaded.
         */

        QString url() const
        {
            return mUrl;
        }

        void setUrl(QString mUrl)
        {
            this->mUrl = mUrl;
        }

        /*! Volume associated with this document, for example, a book volume, or a journal volume.
         */

        int volume() const
        {
            return mVolume;
        }

        void setVolume(int mVolume)
        {
            this->mVolume = mVolume;
        }

        /*! Year where this document was published or created.
         */

        int year() const
        {
            return mYear;
        }

        void setYear(int mYear)
        {
            this->mYear = mYear;
        }

        /*! Keywords associated with this document, this keywords will be used for search and tagging.
         */

        const QStringList keywords() const
        {
            return mKeywords;
        }

        void setKeywords(const QStringList& keywords)
        {
            mKeywords = keywords;
        }

        /*! Editors of this document.
         * This field is separate from authors to accomodate articles and books with authors and editors.
         */

        QStringList editors() const
        {
            return mEditors;
        }

        void setEditors(const QStringList& editors)
        {
            mEditors = editors;
        }

        /*! Range of pages where this document can be found.
         */
        PageRange pages() const
        {
            return mPages;
        }

        void setPages(const PageRange& pages)
        {
            mPages = pages;
        }

        /*! Series of books/journals where this document can be found.
         */

        QString series() const
        {
            return mSeries;
        }

        void setSeries(const QString& series)
        {
            mSeries = series;
        }

        /*! Associated subtitle for this document, usually for collections. For example, for a book containing
         * several articles, the title of the document should be in subTitle()
         * and the title of the book should be in title().
         */

        QString subTitle() const
        {
            return mSubTitle;
        }

        void setSubTitle(const QString& superTitle)
        {
            mSubTitle = superTitle;
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
    QStringList mAuthors;

    bool mIsPublished;
    bool mIsPeerReviewed;

    DocumentType mType;
    Journal::Ptr mJournal;

    QStringList mKeywords;
    QString mSeries;
    QString mSubTitle;
    QStringList mEditors;
    PageRange mPages;
};

#endif /* PUBLICATION_H_ */
