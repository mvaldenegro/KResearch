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

#include "CollectionDockWidget.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QPalette>
#include <QDebug>

#include <KIcon>

CollectionDockWidget::CollectionDockWidget(QWidget *parent)
 : QDockWidget("Collections", parent)
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setObjectName("collectionDockWidget");

    setupLibraryTree();

    connect(mTree, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(itemActivated(QTreeWidgetItem *, int)));
}

CollectionDockWidget::~CollectionDockWidget()
{
}

void CollectionDockWidget::setupLibraryTree()
{
    mTree = new QTreeWidget(this);


    mTree->setColumnCount(1);
    mTree->setHeaderHidden(true);
    mTree->setIndentation(10);
    mTree->setIconSize(QSize(32, 32));

    //mTree->setStyleSheet("QTreeView::branch:has-children {image: url(:/images/1rightarrow.png)}"
    //                     "QTreeView::branch:open {image: url(:/images/1downarrow.png)}");

    QFont font = QTreeWidgetItem().font(0);
    font.setBold(true);

    mLibraryItem = new QTreeWidgetItem(mTree, QStringList("Library"));
    mLibraryItem->setFont(0, font);

    QTreeWidgetItem *articles = new QTreeWidgetItem(mLibraryItem, QStringList("Articles"));
    articles->setIcon(0, KIcon("document-multiple"));
    QTreeWidgetItem *authors = new QTreeWidgetItem(mLibraryItem, QStringList("Authors"));
    authors->setIcon(0, KIcon("user-identity"));
    QTreeWidgetItem *journals  = new QTreeWidgetItem(mLibraryItem, QStringList("Journals"));
    journals->setIcon(0, KIcon("application-epub+zip"));

    mResearchItem = new QTreeWidgetItem(mTree, QStringList("Research"));
    mResearchItem->setFont(0, font);

    QTreeWidgetItem *notes = new QTreeWidgetItem(mResearchItem, QStringList("Notes"));
    notes->setIcon(0, KIcon("folder-txt"));

    mSourcesItem = new QTreeWidgetItem(mTree, QStringList("Sources"));
    mSourcesItem->setFont(0, font);

    (new QTreeWidgetItem(mSourcesItem, QStringList("Conferences")))->setIcon(0, KIcon("meeting-attending"));
    (new QTreeWidgetItem(mSourcesItem, QStringList("Periodicals")))->setIcon(0, KIcon("knewsticker"));
    (new QTreeWidgetItem(mSourcesItem, QStringList("Web")))->setIcon(0, KIcon("document-open-remote"));

    mCollectionsItem  = new QTreeWidgetItem(mTree, QStringList("Collections"));
    mCollectionsItem->setFont(0, font);

    mTree->expandAll();

    setWidget(mTree);
}

void CollectionDockWidget::itemActivated(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);

    emit changeView(item->text(0));
}
