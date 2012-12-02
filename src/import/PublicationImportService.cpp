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

#include "PublicationImportService.h"

#include <import/DocumentImportWizard.h>
#include <import/importers/ImportService.h>
#include <library/dao/DocumentDAO.h>

#include <QFileInfo>
#include <QDebug>

PublicationImportService::PublicationImportService(DocumentDAO *pubDAO)
: mPubDAO(pubDAO)
{
}

PublicationImportService::~PublicationImportService()
{
}

bool PublicationImportService::import(const QString& fileName)
{
    qDebug() << "Attempting to import" << fileName;

    QFileInfo info(fileName);

    if(!info.isFile()) {
        return false;
    }

    if(isAcceptedSuffix(info.completeSuffix())) {

        Document::List pubs = ImportService::self()->import(fileName);
        Document::Ptr pub;

        if(pubs.count() > 0) {
            pub = pubs.at(0);
        } else {
            pub = new Document();
        }

        //pub->setTitle(info.baseName());
        //pub->setLocalUrl(fileName);

        bool ok = DocumentImportWizard::importPublication(pub);

        if(ok) {
            publicationDAO()->saveOrUpdate(pub);
        }

        return ok;
    }

    return false;
}

bool PublicationImportService::isAcceptedSuffix(const QString& suffix) const
{
    QString ext = suffix.toLower();

    if(ext == "pdf" || ext == "ps") {
        return true;
    }

    return false;
}
