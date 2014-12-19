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

#include "CollectionTreeItem.h"

#include <QVariant>
#include <QDebug>

CollectionTreeItem::CollectionTreeItem(CollectionTreeItem *parent)
 : mParent(parent), mActivated(nullptr)
{
    setActivatedCallback([this]() {
        qDebug() << "Item" << this->name() << "activated";
    });
}

CollectionTreeItem::CollectionTreeItem(const QString& name, CollectionTreeItem *parent)
: mParent(parent), mName(name), mActivated(nullptr)
{
    setActivatedCallback([this]() {
        qDebug() << "Item" << this->name() << "activated";
    });
}

CollectionTreeItem::CollectionTreeItem(const QString& name, const QIcon& icon, CollectionTreeItem *parent)
: mParent(parent), mName(name), mIcon(icon), mActivated(nullptr)
{
    setActivatedCallback([this]() {
        qDebug() << "Item" << this->name() << "activated";
    });
}

CollectionTreeItem::~CollectionTreeItem()
{
}

int CollectionTreeItem::row() const
{
    if(parent()) {
        return parent()->mChildrens.indexOf(const_cast<CollectionTreeItem *>(this));
    }

    return 0;
}

void CollectionTreeItem::appendChild(CollectionTreeItem *item)
{
    if(!mChildrens.contains(item)) {
        item->setParent(this);

        mChildrens.append(item);
    }
}

QVariant CollectionTreeItem::data(int role) const
{
    switch(role) {
        case Qt::DisplayRole: {
            return mName;
        }

        case Qt::DecorationRole: {
            return mIcon;
        }

        default: {
            return QVariant();
        }
    }
}
