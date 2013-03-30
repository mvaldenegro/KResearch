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

#include "DocumentImportService.h"

#include <import/DocumentImportWizard.h>
#include <import/importers/PDFDocumentImporter.h>
#include <import/importers/BibtexDocumentImporter.h>
#include <library/dao/DocumentDAO.h>
#include <library/Repository.h>

#include <QFileInfo>
#include <QDebug>

#include <assert.h>

DocumentImportService *DocumentImportService::mSelf = nullptr;

DocumentImportService::DocumentImportService(DocumentDAO *pubDAO)
: mPubDAO(pubDAO)
{
    assert(mSelf == 0);

    mSelf = this;

    registerImporter(new PDFDocumentImporter());
    registerImporter(new BibtexDocumentImporter());
}

DocumentImportService::~DocumentImportService()
{
}

bool DocumentImportService::importIntoLibrary(const QString& fileName)
{
    qDebug() << "Attempting to import" << fileName;

    if(!QFileInfo(fileName).isFile()) {
        return false;
    }

    Document::List docs = import(fileName);

    if(docs.count() > 1) {

        return multipleImportIntoLibrary(docs);

    } else if (docs.count() == 1) {
        Document::Ptr doc = docs.at(0);

        bool ok = DocumentImportWizard::importDocument(doc);

        if(ok) {
            documentDAO()->saveOrUpdate(doc);
        }

        return ok;
    }

    return false;
}

bool DocumentImportService::multipleImportIntoLibrary(Document::List docs)
{
    documentDAO()->beginTransaction();

    for(Document::Ptr doc: docs) {
        documentDAO()->saveOrUpdate(doc);
    }

    documentDAO()->endTransaction();

    return true;
}

Document::List DocumentImportService::import(const QString& localFilename) const
{
    Document::List ret;
    KMimeType::Ptr mimeType = KMimeType::findByPath(localFilename);
    DocumentImporter *importer = importerForMimeType(mimeType);

    qDebug() << "Finding importer for mimeType" << mimeType->name();

    if(importer) {
        ret = importer->import(localFilename);

        qDebug("Importer found");
    } else {
        ret = Document::List();

        qDebug("Importer not found!");
    }

    return ret;
}

DocumentImporter *DocumentImportService::importerForMimeType(const KMimeType::Ptr& mimeType) const
{
    for(DocumentImporter *importer: mImporters) {
        KMimeType::List mimeTypes = importer->mimeTypes();

        for(KMimeType::Ptr imptMime: mimeTypes) {
            if(imptMime->name() == mimeType->name()) {
                return importer;
            }
        }
    }

    return 0;
}

void DocumentImportService::registerImporter(DocumentImporter *importer)
{
    if(!mImporters.contains(importer)) {

        mImporters.append(importer);
    }
}

void DocumentImportService::removeImporter(DocumentImporter *importer)
{
    mImporters.removeAll(importer);
}

DocumentImportService *DocumentImportService::self()
{
    if(mSelf == nullptr) {
        mSelf = new DocumentImportService(Repository::self()->publicationDAO());
    }
    
    return mSelf;
}
