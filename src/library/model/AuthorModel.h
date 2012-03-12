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

#ifndef AUTHORMODEL_H_
#define AUTHORMODEL_H_

#include <QAbstractItemModel>

#include <library/dao/AuthorDAO.h>

class AuthorModel : public QAbstractItemModel
{
    Q_OBJECT

    public:
        AuthorModel(AuthorDAO *authorDAO);
        virtual ~AuthorModel();

        virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
        virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
        virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

        bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);

        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
        virtual QModelIndex parent(const QModelIndex& index) const;

        Qt::ItemFlags flags(const QModelIndex &index) const;

    public Q_SLOTS:
        void invalidateData();

    private:

        QVariant handleColumnNames(int column) const;
        QVariant handleRead(Author::Ptr author, int column) const;
        bool handleWrite(Author::Ptr author, const QVariant& value, int column);

        AuthorDAO *mAuthorDAO;
};

#endif /* AUTHORMODEL_H_ */
