/*
 * Copyright (C) 2011-2012 Matias Valdenegro <matias.valdenegro@gmail.com>
 * This file is part of kresearch.
 *
 * kresearch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * kresearch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with kresearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PreviewTab.h"

#include <KDE/KUrl>
#include <KDE/KMimeType>
#include <KDE/KMimeTypeTrader>
#include <KDE/KService>

#include <KParts/Part>

#include <QDebug>

PreviewTab::PreviewTab(QWidget *parent, const QString& fileName)
 : KVBox(parent)
{
    setUrl(fileName);
}

PreviewTab::~PreviewTab()
{
}

void PreviewTab::setUrl(const QString& fileName)
{
    KMimeType::Ptr mime = KMimeType::findByFileContent(fileName);

    qDebug() << "Got mimetype" << mime->name();

    mPart = KMimeTypeTrader::createPartInstanceFromQuery<KParts::ReadOnlyPart>(mime->name(), this);

    if(mPart) {
        mPart->openUrl(KUrl::fromLocalFile(fileName));
        mPart->widget()->setParent(this);
    }
}
