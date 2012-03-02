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

}

CollectionDockWidget::~CollectionDockWidget()
{
}

void CollectionDockWidget::setupLibraryTree()
{
    mTree = new QTreeWidget(this);

    QPalette p = mTree->palette();
    //p.setColor(QPalette::Active, QPalette::Background, p.color(QPalette::Active, QPalette::Window));
    //mTree->setPalette(p);
    //mTree->setAutoFillBackground(false);
    //mTree->setStyleSheet("QTreeView { background-color: palette(window); }");

    //qDebug() << "Active window color" << p.color(QPalette::Active, QPalette::Window);

    //mTree->setFrameShadow(QFrame::Plain);
    //mTree->setFrameShape(QFrame::StyledPanel);

    mTree->setColumnCount(1);
    mTree->setHeaderHidden(true);
    mTree->setIndentation(10);
    //mTree->setFrameStyle(QFrame::NoFrame);
    //mTree->setLineWidth(0);
    mTree->setIconSize(QSize(32, 32));

    //mTree->setStyleSheet("QTreeView::branch:has-children {image: url(:/images/1rightarrow.png)}"
    //                     "QTreeView::branch:open {image: url(:/images/1downarrow.png)}");

    QFont font = QTreeWidgetItem().font(0);
    font.setBold(true);

    mLibraryItem = new QTreeWidgetItem(mTree, QStringList("Library"));
    mLibraryItem->setFont(0, font);

    (new QTreeWidgetItem(mLibraryItem, QStringList("Articles")))->setIcon(0, KIcon("document-multiple"));
    (new QTreeWidgetItem(mLibraryItem, QStringList("Books")))->setIcon(0, KIcon("documentation"));
    (new QTreeWidgetItem(mLibraryItem, QStringList("Patents")))->setIcon(0, KIcon("view-bank"));
    (new QTreeWidgetItem(mLibraryItem, QStringList("Miscellaneous")))->setIcon(0, KIcon("page-simple"));

    mResearchItem = new QTreeWidgetItem(mTree, QStringList("Research"));
    mResearchItem->setFont(0, font);

    (new QTreeWidgetItem(mResearchItem, QStringList("Notes")))->setIcon(0, KIcon("folder-txt"));

    mSourcesItem      = new QTreeWidgetItem(mTree, QStringList("Sources"));
    mSourcesItem->setFont(0, font);

    (new QTreeWidgetItem(mSourcesItem, QStringList("Authors")))->setIcon(0, KIcon("user-identity"));
    (new QTreeWidgetItem(mSourcesItem, QStringList("Conferences")))->setIcon(0, KIcon("meeting-attending"));
    (new QTreeWidgetItem(mSourcesItem, QStringList("Journals")))->setIcon(0, KIcon("application-epub+zip"));
    (new QTreeWidgetItem(mSourcesItem, QStringList("Periodicals")))->setIcon(0, KIcon("knewsticker"));
    (new QTreeWidgetItem(mSourcesItem, QStringList("Web")))->setIcon(0, KIcon("document-open-remote"));

    mCollectionsItem  = new QTreeWidgetItem(mTree, QStringList("Collections"));
    mCollectionsItem->setFont(0, font);

    mTree->expandAll();

    setWidget(mTree);
}
