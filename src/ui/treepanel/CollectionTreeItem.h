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

#ifndef COLLECTIONTREEITEM_H_
#define COLLECTIONTREEITEM_H_

#include <QList>
#include <QString>
#include <QIcon>

#include <functional>

class CollectionTreeItem
{
    public:

        typedef std::function<void ()> Callback;

        CollectionTreeItem(CollectionTreeItem *parent = 0);
        CollectionTreeItem(const QString& name, CollectionTreeItem *parent = 0);
        CollectionTreeItem(const QString& name, const QIcon& icon, CollectionTreeItem *parent = 0);
        virtual ~CollectionTreeItem();

        int childCount() const
        {
            return mChildrens.count();
        }

        CollectionTreeItem *parent() const
        {
            return mParent;
        }

        CollectionTreeItem *child(int row)
        {
            return mChildrens.at(row);
        }

        CollectionTreeItem *childByName(const QString& name)
        {
            for(CollectionTreeItem *child: mChildrens) {
                if(child && child->name() == name) {
                    return child;
                }
            }

            return nullptr;
        }

        int row() const;

        void appendChild(CollectionTreeItem *item);

        QVariant data(int role) const;

        QList<CollectionTreeItem *> childrens() const
        {
            return mChildrens;
        }

        QIcon icon() const
        {
            return mIcon;
        }

        void setIcon(const QIcon& icon)
        {
            mIcon = icon;
        }

        QString name() const
        {
            return mName;
        }

        void setName(const QString& name)
        {
            mName = name;
        }

        void setActivatedCallback(Callback activated)
        {
            mActivated = activated;
        }

        void activate()
        {
            if(mActivated != nullptr) {
                mActivated();
            }
        }

    protected:
        void setParent(CollectionTreeItem *parent)
        {
            mParent = parent;
        }

    private:
        QList<CollectionTreeItem *> mChildrens;
        CollectionTreeItem *mParent;

        QString mName;
        QIcon mIcon;

        Callback mActivated;

};

#endif /* COLLECTIONTREEITEM_H_ */
