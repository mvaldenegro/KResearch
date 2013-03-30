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

#ifndef SERIALIZATIONUTILS_H_
#define SERIALIZATIONUTILS_H_

class SerializationUtils
{
    public:
        inline static QString serialize(QList<qulonglong> values)
        {
            QStringList ret;

            for(qulonglong value: values) {
                ret += QString::number(value);
            }

            return ret.join(",");
        }

        inline static QList<qulonglong> deserializeListULongLong(const QString& str)
        {
            QStringList separated = str.split(',');
            QList<qulonglong> ret;

            for(QString value: separated) {
                ret += value.toULongLong();
            }

            return ret;
        }
};

#endif /* SERIALIZATIONUTILS_H_ */
