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

#ifndef KEYWORD_H_
#define KEYWORD_H_

#include <library/BaseEntity.h>
#include <library/Document.h>

class Keyword : public BaseEntity
{
    public:
        typedef Keyword * Ptr;
        typedef QList<Ptr> List;

        Keyword();
        virtual ~Keyword();

        const QString& name() const
        {
            return mName;
        }

        void setName(const QString& name)
        {
            mName = name;
        }

        Document::List documents() const
        {
            return mDocuments;
        }

        void setDocuments(const Document::List& documents)
        {
            mDocuments = documents;
        }

    private:
        QString mName;
        Document::List mDocuments;

};

#endif /* KEYWORD_H_ */
