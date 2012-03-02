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

#ifndef PUBLICATIONSTATUS_H_
#define PUBLICATIONSTATUS_H_

class PublicationStatus
{
    public:

        enum Type
        {
            Unpublished,
            Published,
            PeerReviewed,
            NonPeerReviewed
        };

        PublicationStatus();
        ~PublicationStatus();

        QString toString() const;

        unsigned int toUInt() const;

        static PublicationStatus fromString(const QString& str);

    private:
        static QHash<unsigned int, QString> mStringHash;

        Type mEnumValue;
};

#endif /* PUBLICATIONSTATUS_H_ */
