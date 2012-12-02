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

#include "ImportService.h"

#include <import/importers/PDFDocumentImporter.h>

#include <KMimeType>

#include <QDebug>

ImportService *ImportService::mSelf = 0;

ImportService::ImportService()
{
    registerImporter(new PDFDocumentImporter());
}

ImportService::~ImportService()
{
}

Document::List ImportService::import(const QString& localFilename) const
{
    Document::List ret;
    KMimeType::Ptr mimeType = KMimeType::findByFileContent(localFilename);
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

DocumentImporter *ImportService::importerForMimeType(const KMimeType::Ptr& mimeType) const
{
    foreach(DocumentImporter *importer, mImporters) {
        KMimeType::List mimeTypes = importer->mimeTypes();

        foreach(KMimeType::Ptr imptMime, mimeTypes) {
            if(imptMime->name() == mimeType->name()) {
                return importer;
            }
        }
    }

    return 0;
}

void ImportService::registerImporter(DocumentImporter *importer)
{
    if(!mImporters.contains(importer)) {

        mImporters.append(importer);
    }
}

void ImportService::removeImporter(DocumentImporter *importer)
{
    mImporters.removeAll(importer);
}

ImportService *ImportService::self()
{
    if(!mSelf) {
        mSelf = new ImportService();
    }

    return mSelf;
}
