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

    connect(mTreeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(itemActivated(const QModelIndex&)));
}

CollectionDockWidget::~CollectionDockWidget()
{
}

void CollectionDockWidget::setupLibraryTree()
{
    mTreeView = new QTreeView(this);

    mTreeView->setHeaderHidden(true);
    //mTree->setIndentation(10);
    mTreeView->setIconSize(QSize(24, 24));

    //mTree->setStyleSheet("QTreeView::branch:has-children {image: url(:/images/1rightarrow.png)}"
    //                     "QTreeView::branch:open {image: url(:/images/1downarrow.png)}");

    mTree = new CollectionTree();

    mTreeModel = new CollectionTreeModel(this);
    mTreeModel->setTree(mTree);

    mTreeView->setModel(mTreeModel);
    mTreeView->expandAll();

    QFont font = mTreeView->font();
    font.setBold(true);
    mTreeView->setFont(font);

    setWidget(mTreeView);
}

void CollectionDockWidget::itemActivated(const QModelIndex& index)
{
    qDebug() << "Activating index" << index.internalPointer();

    if(!index.isValid()) {
        return;
    }

    CollectionTreeItem *item = static_cast<CollectionTreeItem *>(index.internalPointer());

    if(item != nullptr) {
        item->activate();
    }
}
