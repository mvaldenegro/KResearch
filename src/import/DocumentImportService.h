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

#ifndef PUBIMPORTSERVICE_H_
#define PUBIMPORTSERVICE_H_

#include <QString>

#include <import/importers/DocumentImporter.h>
#include <library/Document.h>

class DocumentDAO;

class DocumentImportService
{
    public:
        DocumentImportService(DocumentDAO *pubDAO);
        virtual ~DocumentImportService();

        bool importIntoLibrary(const QString& fileName);
        bool multipleImportIntoLibrary(Document::List docs);

        Document::List import(const QString& localFilename) const;
        DocumentImporter *importerForMimeType(const KMimeType::Ptr& mime) const;

        void registerImporter(DocumentImporter *importer);
        void removeImporter(DocumentImporter *importer);

        static DocumentImportService *self();

    protected:
        DocumentDAO *documentDAO() const
        {
            return mPubDAO;
        }

    private:
        DocumentDAO *mPubDAO;
        QList<DocumentImporter *> mImporters;

        static DocumentImportService *mSelf;
};

#endif /* PUBIMPORTSERVICE_H_ */
