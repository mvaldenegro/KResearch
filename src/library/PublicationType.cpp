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

#include "PublicationType.h"

static QHash<unsigned int, QString> createPublicationHash()
{
    QHash<unsigned int, QString> ret;

    ret.insert(PublicationType::Unpublished             , "Unpublished");
    ret.insert(PublicationType::Article                 , "Article");
    ret.insert(PublicationType::ConferenceArticle       , "Conference Article");
    ret.insert(PublicationType::Book                    , "Book");
    ret.insert(PublicationType::Booklet                 , "Booklet");
    ret.insert(PublicationType::BookChapter             , "Book Chapter");
    ret.insert(PublicationType::BookPart                , "Book part");
    ret.insert(PublicationType::BachelorThesis          , "Bachelor Thesis");
    ret.insert(PublicationType::MasterThesis            , "Master Thesis");
    ret.insert(PublicationType::DoctoralThesis          , "Doctoral Thesis");
    ret.insert(PublicationType::TechnicalReport         , "Technical Report");
    ret.insert(PublicationType::TechnicalDocumentation  , "Technical Documentation");
    ret.insert(PublicationType::OtherDocument           , "Other document type");

    return ret;
}

QHash<unsigned int, QString> PublicationType::mStringHash = createPublicationHash();

PublicationType::PublicationType(Type value)
: mEnumValue(value)
{
}

PublicationType::~PublicationType()
{
}

QString PublicationType::toString() const
{
    return mStringHash.value(mEnumValue);
}

unsigned int PublicationType::toUInt() const
{
    return mEnumValue;
}

PublicationType PublicationType::fromString(const QString& str)
{
    unsigned int key = mStringHash.key(str);

    if(key != 0) {
        return PublicationType((Type) key);
    }

    return PublicationType::Invalid;
}
