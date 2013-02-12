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

#include "PDFDocumentImporter.h"
#include <util/StringUtils.h>
#include <library/dao/AuthorDAO.h>
#include <library/Repository.h>

#include <QRegExp>
#include <QDebug>
#include <QFileInfo>

#include <poppler/qt4/poppler-qt4.h>

PDFDocumentImporter::PDFDocumentImporter()
{
}

PDFDocumentImporter::~PDFDocumentImporter()
{
}

KMimeType::List PDFDocumentImporter::mimeTypes() const
{
    return KMimeType::List() << KMimeType::mimeType("application/pdf");
}

Document::List PDFDocumentImporter::import(const QString& localFilename) const
{
    Document *ret = new Document();
    QFileInfo info(localFilename);
    Poppler::Document *doc = Poppler::Document::load(localFilename);

    if(doc) {
        QString title = getTitle(doc);
        QStringList authors = getAuthors(doc);
        QStringList keywords = getKeywords(doc);

        qDebug() << "Authors:" << authors;

        if(StringUtils::isNullOrEmpty(title)) {
            title = info.fileName();
        }

        ret->setTitle(title);
        ret->setKeywords(keywords);
        ret->setAuthors(authors);
        ret->setLocalUrl(localFilename);

        delete doc;
    }

    return Document::List() << ret;
}

Document::List PDFDocumentImporter::import(const KUrl& url) const
{
    return import(url.toLocalFile());
}

static QRegExp separators = QRegExp(",|;|and");

QString PDFDocumentImporter::getTitle(Poppler::Document *doc)
{
    if(doc) {
        if(doc->infoKeys().contains("Title")) {
            return StringUtils::sanitize(doc->info("Title"));
        }
    }

    return QString();
}

QStringList PDFDocumentImporter::getAuthors(Poppler::Document *doc)
{
    if(doc) {
        if(doc->infoKeys().contains("Author")) {
            QString authors = doc->info("Author");

            return StringUtils::sanitize(authors.split(separators, QString::SkipEmptyParts));
        }
    }

    return QStringList();
}


QStringList PDFDocumentImporter::getKeywords(Poppler::Document *doc)
{
    if(doc) {
        if(doc->infoKeys().contains("Keywords")) {
            QString keywords = doc->info("Keywords");

            return StringUtils::sanitize(keywords.split(separators, QString::SkipEmptyParts));
        }
    }

    return QStringList();
}
