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

#include "CollectionTreeModel.h"

#include <KIcon>

CollectionTreeModel::CollectionTreeModel(QObject *parent)
 : QAbstractItemModel(parent)
{
}

CollectionTreeModel::~CollectionTreeModel()
{
}

QVariant CollectionTreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    CollectionTreeItem *item = static_cast<CollectionTreeItem *>(index.internalPointer());

    return item->data(role);
}

Qt::ItemFlags CollectionTreeModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant CollectionTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return "ASDF";
    }

    return QVariant();
}

QModelIndex CollectionTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent)) {
            return QModelIndex();
    }

    CollectionTreeItem *parentItem;

    if(!parent.isValid()) {
        parentItem = tree()->root();
    } else {
        parentItem = static_cast<CollectionTreeItem *>(parent.internalPointer());
    }

    CollectionTreeItem *childItem = parentItem->child(row);

    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

QModelIndex CollectionTreeModel::parent(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return QModelIndex();
    }

    CollectionTreeItem *childItem = static_cast<CollectionTreeItem *>(index.internalPointer());
    CollectionTreeItem *parentItem = childItem->parent();

    if(parentItem == tree()->root()) {
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int CollectionTreeModel::rowCount(const QModelIndex &parent) const
{
    CollectionTreeItem *parentItem;
    if(parent.column() > 0) {
        return 0;
    }

    if(!parent.isValid()) {
        parentItem = tree()->root();
    } else {
        parentItem = static_cast<CollectionTreeItem *>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int CollectionTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}
