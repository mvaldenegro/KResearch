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

#include "LibraryView.h"

#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include <QToolBar>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QComboBox>

#include <KApplication>
#include <KLineEdit>
#include <KIcon>
#include <KFileDialog>

#include <ui/PublicationEditDialog.h>
#include <import/PublicationImportService.h>
#include <library/model/DocumentModel.h>
#include <library/sqlite/SQLiteRepository.h>

LibraryView::LibraryView(QWidget *parent)
 : BaseView(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    mSearchEdit = new KLineEdit(this);
    mArticleView = new QTableView(this);

    setupToolbar();

    layout->addWidget(mToolBar);
    layout->addWidget(mArticleView);

    connect(mArticleView, SIGNAL(activated(const QModelIndex&)), this, SLOT(activated(const QModelIndex&)));
    connect(mArticleView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(clicked(const QModelIndex&)));

    mSearchEdit->setClearButtonShown(true);

    configureTableView(mArticleView);

    mArticleView->setModel(new DocumentModel(Repository::self()->publicationDAO(), Repository::self()->journalDAO()));
    mArticleView->setAcceptDrops(true);


    mSelectedPub = Document::Ptr(0);

    loadConfig();
}

LibraryView::~LibraryView()
{
    saveConfig();
}

void LibraryView::saveConfig()
{
    KSharedConfigPtr config = KGlobal::config();

    config->group("libraryview").writeEntry("headerstate", mArticleView->horizontalHeader()->saveState());

    config->sync();
}

void LibraryView::loadConfig()
{
    KSharedConfigPtr config = KGlobal::config();

    QByteArray headerState = config->group("libraryview").readEntry("headerstate", QByteArray());

    mArticleView->horizontalHeader()->restoreState(headerState);
}

void LibraryView::import()
{
    QString fileName = KFileDialog::getOpenFileName(KUrl(), QString(), this, "Open file to import");

    if(fileName.isNull() || fileName.isEmpty()) {
        return;
    }

    importService()->import(fileName);
}

void LibraryView::edit()
{
    if(selectedPublication()) {
        PublicationEditDialog::editPublication(selectedPublication());
    }
}

void LibraryView::activated(const QModelIndex& idx)
{
    if(!idx.isValid()) {
        return;
    }

    QString localFileName = Repository::self()->publications()->findAll().at(idx.row())->localUrl();

    qDebug() << "Activated" << localFileName;

    if(!localFileName.isNull() || !localFileName.isEmpty()) {
        emit activated(localFileName);
    }
}

void LibraryView::clicked(const QModelIndex &idx)
{
    if(!idx.isValid()) {
        return;
    }

    Document::Ptr pub = Repository::self()->publications()->findAll().at(idx.row());

    if(pub != 0) {

        mSelectedPub = pub;

        emit selected(pub);
    }
}

void LibraryView::setupToolbar()
{
    QToolBar *bar = new QToolBar(this);

    QAction *import = bar->addAction(KIcon("document-import"), "Import");
    connect(import, SIGNAL(triggered()), this, SLOT(import()));

    QMenu *menu = new QMenu();
    QAction *xport = new QAction("Export to BibTex", this);
    menu->addAction(xport);

    QToolButton* toolButton = new QToolButton();
    toolButton->setMenu(menu);
    toolButton->setIcon(KIcon("document-export"));
    toolButton->setPopupMode(QToolButton::InstantPopup);
    bar->addWidget(toolButton);

    QAction *edit = bar->addAction(KIcon("document-edit"), "Edit");
    QAction *print = bar->addAction(KIcon("document-print"), "Print");
    QAction *dlte = bar->addAction(KIcon("edit-delete"), "Delete");

    bar->addSeparator();

    QAction *newColl = bar->addAction(KIcon("folder-new"), "Create new collection");
    QAction *notes = bar->addAction(KIcon("view-pim-notes"), "View/Edit notes");

    bar->addWidget(mSearchEdit);

    QComboBox *searchCombo = new QComboBox();
    searchCombo->addItems(QStringList() << "Title" << "Author" << "Journal");

    bar->addWidget(searchCombo);
    bar->addAction(KIcon("configure"), "Configure");

    mToolBar = bar;

    connect(edit, SIGNAL(triggered()), this, SLOT(edit()));
}
