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

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <KMainWindow>

class CollectionDockWidget;
class InformationDockWidget;
class LibraryView;

class KTabWidget;
class KStatusNotifierItem;

class MainWindow : public KMainWindow
{
    Q_OBJECT

	public:
		MainWindow(QWidget *parent = 0);
		virtual ~MainWindow();

	public Q_SLOTS:
	    void openPreview(const QString& fileName);
	    void tabCloseRequested(int index);

	protected:
	    void loadConfig();
	    void saveConfig();

	    virtual void closeEvent(QCloseEvent *event);

	private:
	    void setupDockWidgets();

		CollectionDockWidget *mLeftDock;
		InformationDockWidget *mRightDock;
		LibraryView *mLibraryView;

		KTabWidget *mTabWidget;
		KStatusNotifierItem *mTrayIcon;

};

#endif /* MAINWINDOW_H_ */
