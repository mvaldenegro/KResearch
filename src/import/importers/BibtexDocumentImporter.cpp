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

#include "BibtexDocumentImporter.h"
#include "BibtexParser.h"

#include <QFile>
#include <QTextStream>

BibtexDocumentImporter::BibtexDocumentImporter()
{
}

BibtexDocumentImporter::~BibtexDocumentImporter()
{
}

KMimeType::List BibtexDocumentImporter::mimeTypes() const
{
    return KMimeType::List() << KMimeType::mimeType("text/x-bibtex");
}

Document::List BibtexDocumentImporter::import(const QString& localFilename) const
{
    QFile file(localFilename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return Document::List();
    }

    QTextStream stream(&file);
    QString text = stream.readAll();

    return BibtexParser().parse(text);
}

Document::List BibtexDocumentImporter::import(const KUrl& url) const
{
    return import(url.pathOrUrl());
}
