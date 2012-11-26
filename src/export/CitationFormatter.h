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

#ifndef CITATIONFORMATTER_H_
#define CITATIONFORMATTER_H_

#include <library/Publication.h>


/*! Interface for citation formatters.
 *
 * A implementation of this interface should be able to format citation to a document.
 */
class CitationFormatter
{
    public:
        CitationFormatter();
        virtual ~CitationFormatter();

        /*! Format a citation, and return the result as a QString.
         */
        virtual QString format(const Publication::Ptr& publication) const;
};

#endif /* CITATIONFORMATTER_H_ */
