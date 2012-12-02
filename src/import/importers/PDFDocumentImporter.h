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

#ifndef PDFDOCUMENTIMPORTER_H_
#define PDFDOCUMENTIMPORTER_H_

#include <import/importers/DocumentImporter.h>

namespace Poppler {
    class Document;
}

class PDFDocumentImporter : public DocumentImporter
{
    public:
        PDFDocumentImporter();
        virtual ~PDFDocumentImporter();

        KMimeType::List mimeTypes() const;

        Document::List import(const QString& localFilename) const;
        Document::List import(const KUrl& url) const;


    private:

        Author::List parseAuthors(const QStringList& authors) const;

        static QString getTitle(Poppler::Document *doc);
        static QStringList getAuthors(Poppler::Document *doc);
        static QStringList getKeywords(Poppler::Document *doc);
};

#endif /* PDFDOCUMENTIMPORTER_H_ */
