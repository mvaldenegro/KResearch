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

        inline static QString removeBraces(const QString& str)
        {
            QString tmp = QString(str).remove('{');
            return tmp.remove('}');
        }

    public:
        /*This function splits a QString at each comma, but skips splitting between pairs of quotes (" ... "),
         * or between braces ({ .... }).
         */
        inline static QStringList splitWithCommas(const QString& str)
        {
            const QChar comma = QChar(',');
            const QChar quote = QChar('"');
            const QChar openingBrace = QChar('{');
            const QChar closingBrace = QChar('}');

            QStringList ret;
            int start = 0;
            int i = 0;

            for(i = 0; i < str.length(); i++) {
                if(str[i] == comma) {
                    QString part = str.mid(start, i - start);
                    start = i+1;
                    ret.append(part);
                }

                if(str[i] == quote) {
                    for(i++; str[i] != quote; i++) {}
                }

                if(str[i] == openingBrace) {
                    for(i++; str[i] != closingBrace; i++) {}
                }
            }

            ret.append(str.mid(start, i - start));

            return ret;
        }

        inline static QString serialize(const QStringList& strings)
        {
            QStringList tmp;

            for(QString str: strings) {
                tmp += QString("{") + str + QString("}");
            }

            return tmp.join(",");
        }

        inline static QStringList deserialize(const QString& str)
        {
            QStringList tmp = splitWithCommas(str);
            QStringList ret;

            for(QString s: tmp) {
                ret += removeBraces(s);
            }

            return ret;
        }

};

#endif /* STRINGUTILS_H_ */
