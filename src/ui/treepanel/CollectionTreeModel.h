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

#ifndef COLLECTIONTREEMODEL_H_
#define COLLECTIONTREEMODEL_H_

#include <QAbstractItemModel>

#include <ui/treepanel/CollectionTree.h>
#include <ui/treepanel/CollectionTreeItem.h>

class CollectionTreeModel : public QAbstractItemModel
{
        Q_OBJECT

       public:
           explicit CollectionTreeModel(QObject *parent = 0);
           virtual ~CollectionTreeModel();

           QVariant data(const QModelIndex &index, int role) const;
           Qt::ItemFlags flags(const QModelIndex &index) const;
           QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
           QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
           QModelIndex parent(const QModelIndex &index) const;
           int rowCount(const QModelIndex &parent = QModelIndex()) const;
           int columnCount(const QModelIndex &parent = QModelIndex()) const;

        CollectionTree *tree() const
        {
            return mTree;
        }

        void setTree(CollectionTree* tree)
        {
            mTree = tree;
        }

       private:
           CollectionTree *mTree;
};

#endif /* COLLECTIONTREEMODEL_H_ */
