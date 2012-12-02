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

#ifndef NOTE_H_
#define NOTE_H_

#include <library/BaseEntity.h>
#include <library/Document.h>

#include <QList>
#include <QDate>

class Note : public BaseEntity
{
    public:

        typedef Note *Ptr;
        typedef QList<Ptr> List;

        Note();
        ~Note();

        QDate lastModifiedDate() const
        {
            return mLastModifiedDate;
        }

        Document::Ptr document() const
        {
            return mDocument;
        }

        void setLastModifiedDate(QDate mLastModifiedDate)
        {
            this->mLastModifiedDate = mLastModifiedDate;
        }

        void setDocument(Document::Ptr doc)
        {
            this->mDocument = doc;
        }

        void setText(QString mText)
        {
            this->mText = mText;
        }

        QString text() const
        {
            return mText;
        }

private:
    Document::Ptr mDocument;
    QString mText;
    QDate mLastModifiedDate;
};

#endif /* NOTE_H_ */
