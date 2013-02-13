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
 * along with KResearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NAMEUTILS_H_
#define NAMEUTILS_H_

#include <QString>
#include <QStringList>

#include <util/StringUtils.h>

class NameUtils
{
    public:
        /*! Returns the first name of a String composed of "firstname lastname"
         */
        inline static QString firstName(const QString& fullName)
        {
            QStringList parts = parse(fullName);

            if(parts.count() > 0) {
                return parts[0];
            }

            return fullName;
        }

        /*! Returns the last name of a String composed of "firstname lastname"
         */
        inline static QString lastName(const QString& fullName)
        {
            QStringList parts = parse(fullName);

            if(parts.count() > 1) {
                return parts[1];
            }

            return fullName;
        }

        /*! Parse a String containing a name in the following formats:
         * -FirstName <whitespace> LastName
         * -LastName, FirstName
         * Returns a QStringList with two elements, First name in the first element, and Last name in the second.
         */
        inline static QStringList parse(const QString& fullName)
        {
            QStringList parts = fullName.split(',', QString::SkipEmptyParts);

            if(parts.count() == 2) {
                return StringUtils::sanitize(QStringList() << parts[1] << parts[0]);
            }

            parts = fullName.split(' ', QString::SkipEmptyParts);

            if(parts.count() == 2) {
                return StringUtils::sanitize(parts);
            }

            if(parts.count() == 3) {
                return StringUtils::sanitize(QStringList() << (parts[0] + QString(" ") + parts[1]) << parts[2]);
            }

            return QStringList() << fullName;
        }

        inline static QString format(const QStringList& firstAndLastName)
        {
            if(firstAndLastName.count() == 2) {
                return format(firstAndLastName[0], firstAndLastName[1]);
            }

            return firstAndLastName.join(" ");
        }

        inline static QString format(const QString& firstName, const QString& lastName)
        {
            return firstName + QString(" ") + lastName;
        }

        inline static QString normalize(const QString& rawName)
        {
            return format(parse(rawName));
        }
};


#endif /* NAMEUTILS_H_ */
