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

#include "Document.h"

PageRange::PageRange()
: mPageStart(0), mPageEnd(0)
{
}

PageRange::~PageRange()
{
}

QString PageRange::toString()
{
    return QString("%1;%2").arg(pageStart()).arg(pageEnd());
}

PageRange PageRange::fromString(const QString& str)
{
    QStringList parts = str.split(';');
    PageRange ret;

    if(parts.count() == 2) {
        ret.setPageStart(parts[0].toInt());
        ret.setPageEnd(parts[1].toInt());
    }

    return ret;
}

Document::Document()
: BaseEntity(), mYear(0), mVolume(0), mNumber(0), mIsPublished(false), mIsPeerReviewed(false), mJournal(0)
{
}

Document::Document(const Document& copy)
: mTitle(copy.title()), mAbstract(copy.abstract()), mYear(copy.year()),
  mConference(copy.conference()), mPublisher(copy.publisher()), mVolume(copy.volume()),
  mNumber(copy.number()), mUrl(copy.url()), mDoi(copy.doi()), mIsbn(copy.isbn()),
  mLocalURL(copy.localUrl()), mAuthors(copy.authors()), mIsPublished(copy.isPublished()),
  mIsPeerReviewed(copy.isPeerReviewed()), mType(copy.type()), mJournal(copy.journal()),
  mKeywords(copy.keywords())
{

}

Document::~Document()
{
}

