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
 * along with Epic Framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DOCUMENTIMPORTER_H_
#define DOCUMENTIMPORTER_H_

#include <KUrl>
#include <KMimeType>

#include <library/Document.h>


/*! This is the common interface to all document importers.
 *
 * An implementation of this interface should import a document on a local file
 * or from a URL into a Publication instance, and return a list with all documents imported.
 * Multiple documents can be imported from one file or URL.
 */
class DocumentImporter
{
    public:
        DocumentImporter();
        virtual ~DocumentImporter();

        /*! Mime types that this importer can import.
         *
         */
        virtual KMimeType::List mimeTypes() const = 0;

        /*! Imports a local file.
         *
         */
        virtual Document::List import(const QString& localFilename) const = 0;

        /*! Imports a URL.
         *
         */
        virtual Document::List import(const KUrl& url) const = 0;
};

#endif /* DOCUMENTIMPORTER_H_ */
