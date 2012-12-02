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

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <QString>
#include <QStringList>

class StringUtils
{
    public:
        inline static bool isNullOrEmpty(const QString& str)
        {
            return str.isNull() || str.isEmpty();
        }

        inline static QString sanitize(const QString& str)
        {
            return str.trimmed();
        }

        inline static QStringList sanitize(const QStringList& strings)
        {
            QStringList ret;

            foreach(QString str, strings) {
                ret.append(sanitize(str));
            }

            return ret;
        }
};

#endif /* STRINGUTILS_H_ */
