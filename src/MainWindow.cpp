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

#include "MainWindow.h"
#include "LibraryView.h"
#include "AuthorView.h"
#include "JournalView.h"

#include <ui/PreviewTab.h>
#include <ui/InformationDockWidget.h>
#include <ui/CollectionDockWidget.h>
#include <ui/ConcealedTabWidget.h>

#include <ui/infopanel/InfoPanelDock.h>

#include <QDebug>
#include <QStackedWidget>

#include <KSharedConfig>
#include <KGlobal>
#include <KConfig>
#include <KStatusNotifierItem>

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
: KMainWindow(parent)
{
    setCaption("KResearch");

    mTabWidget = new ConcealedTabWidget(this);
    mTabWidget->setTabsClosable(true);

    mViewWidget = new QStackedWidget(this);

    mLibraryView = new LibraryView(this);
    mAuthorView = new AuthorView(this);
    mJournalView = new JournalView(this);

    mViewWidget->addWidget(mLibraryView);
    mViewWidget->addWidget(mAuthorView);
    mViewWidget->addWidget(mJournalView);

    mTabWidget->addTab(mViewWidget, "Articles");

    connect(mLibraryView, SIGNAL(activated(const QString&)), this, SLOT(openPreview(const QString&)));
    connect(mTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequested(int)));

    mTrayIcon = new KStatusNotifierItem(this);
    mTrayIcon->setTitle("KResearch");
    mTrayIcon->setIconByName("kjournal");

    setupDockWidgets();

    setCentralWidget(mTabWidget);

    loadConfig();
}

MainWindow::~MainWindow()
{
}

void MainWindow::openPreview(const QString& fileName)
{
    qDebug() << "Requested preview for" << fileName;

    int idx = mTabWidget->addTab(new PreviewTab(this, fileName), "Preview");
    mTabWidget->setCurrentIndex(idx);
}

void MainWindow::tabCloseRequested(int idx)
{
    // Don't close the tab containing the main view (Library, Author, Journal, etc).
    if(idx == 0) {
        return;
    }

    QWidget *widget = mTabWidget->widget(idx);

    if(widget != 0) {
        mTabWidget->removeTab(idx);

        delete widget;
    }
}

void MainWindow::switchView(const QString& viewName)
{
    bool sw = false;

    if(viewName == "Authors") {
        mViewWidget->setCurrentWidget(mAuthorView);
        mTabWidget->setTabText(0, "Authors");

        sw = true;
    }

    if(viewName == "Articles") {
        mViewWidget->setCurrentWidget(mLibraryView);
        mTabWidget->setTabText(0, "Articles");

        sw = true;
    }

    if(viewName == "Journals") {
        mViewWidget->setCurrentWidget(mJournalView);
        mTabWidget->setTabText(0, "Journals");

        sw = true;
    }

    if(sw) {
        mTabWidget->setCurrentIndex(0);
    }
}

void MainWindow::loadConfig()
{
    KSharedConfigPtr config = KGlobal::config();

    QByteArray geometry = config->group("mainwindow").readEntry("geometry", QByteArray());
    QByteArray state = config->group("mainwindow").readEntry("state", QByteArray());

    restoreGeometry(geometry);
    restoreState(state);
}

void MainWindow::saveConfig()
{
    KSharedConfigPtr config = KGlobal::config();

    config->group("mainwindow").writeEntry("geometry", saveGeometry());
    config->group("mainwindow").writeEntry("state", saveState());
    config->sync();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveConfig();

    KMainWindow::closeEvent(event);
}

void MainWindow::setupDockWidgets()
{
    mLeftDock = new CollectionDockWidget(this);
    mRightDock = new InfoPanelDock(this);

    addDockWidget(Qt::LeftDockWidgetArea, mLeftDock);
    addDockWidget(Qt::RightDockWidgetArea, mRightDock);

    connect(mLibraryView, SIGNAL(selected(Document::Ptr)), mRightDock, SLOT(display(Document::Ptr)));

    connect(mLeftDock, SIGNAL(changeView(const QString&)), this, SLOT(switchView(const QString&)));
}
