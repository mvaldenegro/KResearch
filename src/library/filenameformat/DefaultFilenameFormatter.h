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

#ifndef DEFAULTFILENAMEFORMATTER_H
#define	DEFAULTFILENAMEFORMATTER_H

#include <library/filenameformat/DocumentFilenameFormatter.h>

class DefaultFilenameFormatter : DocumentFilenameFormatter {
    public:
        DefaultFilenameFormatter();
        DefaultFilenameFormatter(const DefaultFilenameFormatter& orig);
        virtual ~DefaultFilenameFormatter();
    
        virtual QString formatFilename(Document::Ptr document) const;
        virtual QString formatLibraryFolder(Document::Ptr document) const;
};

#endif	/* DEFAULTFILENAMEFORMATTER_H */

