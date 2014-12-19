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

#ifndef LIBRARYDOCKWIDGET_H_
#define LIBRARYDOCKWIDGET_H_

#include <QDockWidget>
#include <QTreeView>

#include <ui/treepanel/CollectionTree.h>
#include <ui/treepanel/CollectionTreeModel.h>

class CollectionDockWidget : public QDockWidget
{
    Q_OBJECT

    public:
        CollectionDockWidget(QWidget *parent);
        virtual ~CollectionDockWidget();

    signals:
        void changeView(const QString& viewName);

    protected:
        void setupLibraryTree();

    private Q_SLOTS:
        void itemActivated(const QModelIndex& index);

    private:
        QTreeView *mTreeView;
        CollectionTreeModel *mTreeModel;
        CollectionTree *mTree;
};

#endif /* LIBRARYDOCKWIDGET_H_ */
