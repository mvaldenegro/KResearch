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

#ifndef PUBLICATIONTYPE_H_
#define PUBLICATIONTYPE_H_

#include <QString>
#include <QHash>

class PublicationType
{
    public:

        enum Type
        {
            Unpublished             = 1,
            Article                 = 2,
            ConferenceArticle       = 3,
            Book                    = 4,
            Booklet                 = 5,
            BookChapter             = 6,
            BookPart                = 7,
            BachelorThesis          = 8,
            MasterThesis            = 9,
            DoctoralThesis          = 10,
            TechnicalReport         = 11,
            TechnicalDocumentation  = 12,
            OtherDocument           = 1000,
            Invalid                 = 1001
        };

        PublicationType(Type value);
        ~PublicationType();

        QString toString() const;

        unsigned int toUInt() const;

        static PublicationType fromString(const QString& str);

    private:

        static QHash<unsigned int, QString> mStringHash;

        Type mEnumValue;
};

#endif /* PUBLICATIONTYPE_H_ */
