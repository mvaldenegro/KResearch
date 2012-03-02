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

#include "MainWindow.h"
#include "LibraryView.h"
#include <ui/PreviewTab.h>
#include <ui/InformationDockWidget.h>
#include <ui/CollectionDockWidget.h>

#include <QDebug>

#include <KSharedConfig>
#include <KGlobal>
#include <KConfig>
#include <KTabWidget>
#include <KStatusNotifierItem>

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
: KMainWindow(parent)
{
    setCaption("KResearch");


    mTabWidget = new KTabWidget(this);
    mTabWidget->setTabsClosable(true);

    mLibraryView = new LibraryView(this);

    connect(mLibraryView, SIGNAL(activated(const QString&)), this, SLOT(openPreview(const QString&)));
    connect(mTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseRequested(int)));

    mTabWidget->addTab(mLibraryView, "Library");

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
    QString tabTitle = mTabWidget->tabText(idx);

    if(tabTitle.contains("Library")) {
        return;
    }

    QWidget *widget = mTabWidget->widget(idx);

    if(widget != 0) {
        mTabWidget->removeTab(idx);

        delete widget;
    }
}

void MainWindow::loadConfig()
{
    qDebug() << "loadConfig";


    KSharedConfigPtr config = KGlobal::config();

    QByteArray geometry = config->group("mainwindow").readEntry("geometry", QByteArray());
    QByteArray state = config->group("mainwindow").readEntry("state", QByteArray());

    qDebug() << "geometry state size" << geometry.size();
    qDebug() << "restoreGeometry" << restoreGeometry(geometry);
    qDebug() << "restoreState" << restoreState(state);
}

void MainWindow::saveConfig()
{
    qDebug() << "saveConfig";

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
    mRightDock = new InformationDockWidget(this);

    addDockWidget(Qt::LeftDockWidgetArea, mLeftDock);
    addDockWidget(Qt::RightDockWidgetArea, mRightDock);

    connect(mLibraryView, SIGNAL(selected(Publication::Ptr)), mRightDock, SLOT(display(Publication::Ptr)));
}
