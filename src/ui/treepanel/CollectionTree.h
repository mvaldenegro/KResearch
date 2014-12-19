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

#ifndef COLLECTIONTREE_H_
#define COLLECTIONTREE_H_

#include <ui/treepanel/CollectionTreeItem.h>

class CollectionTree
{
    public:
        CollectionTree();
        virtual ~CollectionTree();

        CollectionTreeItem *collections() const
        {
            return mCollectionsItem;
        }

        CollectionTreeItem *library() const
        {
            return mLibraryItem;
        }

        CollectionTreeItem *root() const
        {
            return mRootItem;
        }

    private:
        CollectionTreeItem *mRootItem;

        CollectionTreeItem *mLibraryItem;
        CollectionTreeItem *mCollectionsItem;
};

#endif /* COLLECTIONTREE_H_ */
