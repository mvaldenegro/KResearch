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

#ifndef IMPORTSERVICE_H_
#define IMPORTSERVICE_H_

#include <library/Document.h>
#include <import/importers/DocumentImporter.h>

#include <QList>

class ImportService
{
    public:
        ImportService();
        virtual ~ImportService();

        Document::List import(const QString& localFilename) const;
        DocumentImporter *importerForMimeType(const KMimeType::Ptr& mime) const;

        void registerImporter(DocumentImporter *importer);
        void removeImporter(DocumentImporter *importer);

        static ImportService *self();

    private:
        QList<DocumentImporter *> mImporters;

        static ImportService *mSelf;
};

#endif /* IMPORTSERVICE_H_ */
