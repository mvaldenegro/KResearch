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

#include "PublicationModel.h"

#include <import/PublicationImportService.h>

#include <QDebug>
#include <QMimeData>
#include <QList>
#include <QUrl>
#include <QStringList>

PublicationModel::PublicationModel(PublicationDAO *pubDAO)
: QAbstractItemModel(), mPublicationDAO(pubDAO)
{
    mImportService = new PublicationImportService(pubDAO);

    connect(pubDAO, SIGNAL(dataChanged()), this, SLOT(invalidateData()));
}

PublicationModel::~PublicationModel()
{
}

int PublicationModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return 5;
}

int PublicationModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return mPublicationDAO->findAll().count();
}
QVariant PublicationModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    int i = index.row();
    int j = index.column();

    if(i < 0 || i > mPublicationDAO->findAll().count()) {
        return QVariant();
    }

    Publication::Ptr pub = mPublicationDAO->findAll().at(index.row());

    if(role == Qt::DisplayRole) {
        return handleRead(pub, j);
    }

    if(role == Qt::EditRole) {
        return handleRead(pub, j);
    }

    return QVariant();
}

bool PublicationModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(index.isValid() && role == Qt::EditRole) {

        Publication::Ptr pub = mPublicationDAO->findAll().at(index.row());
        bool ok = handleWrite(pub, value, index.column());

        if(ok) {
            emit dataChanged(index, index);

            mPublicationDAO->saveOrUpdate(pub);
        }

        return ok;
    }

    return false;
}

QVariant PublicationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal) {
        return QVariant();
    }

    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    return handleColumnNames(section);
}

QModelIndex PublicationModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    //TODO: Use the internalId to do indexing into the DAO.
    return createIndex(row, column, (void *) 0);
}

QModelIndex PublicationModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

Qt::DropActions PublicationModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;
}

Qt::ItemFlags PublicationModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)

    return Qt::ItemIsDropEnabled | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    //return Qt::ItemIsDropEnabled | Qt::ItemIsEnabled;
}

bool PublicationModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                    int row, int column, const QModelIndex& parent)
{
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)

    qDebug() << "dropMimeData";

    if(action == Qt::IgnoreAction) {
        return true;
    }

    if(!data->hasUrls()) {
        return false;
    }

    QList<QUrl> urls = data->urls();

    foreach(QUrl url, urls) {
        qDebug() << "I was dropped" << url;

        mImportService->import(url.path());
    }

    return true;
}

QStringList PublicationModel::mimeTypes() const
{
    return QStringList() << "text/uri-list";
}

void PublicationModel::invalidateData()
{
    beginResetModel();
    endResetModel();
}

QVariant PublicationModel::handleColumnNames(int column) const
{
    switch(column) {
        case 0: {
            return "Title";
        }

        case 1: {
            return "Authors";
        }

        case 2: {
            return "Year";
        }

        case 3: {
            return "Journal";
        }

        case 4: {
            return "Conference";
        }
    }

    return QVariant();
}

QVariant PublicationModel::handleRead(Publication::Ptr pub, int column) const
{
    switch(column) {
        case 0: {
            return pub->title();
        }

        case 1: {
            return formatAuthors(pub->authors());
        }

        case 2: {
            return pub->year();
        }

        case 3: {
            return pub->journal();
        }

        case 4: {
            return pub->conference();
        }
    }

    return QVariant();
}

bool PublicationModel::handleWrite(Publication::Ptr pub, const QVariant& value, int column)
{
    switch(column) {
        case 0: {
            pub->setTitle(value.toString());

            return true;
        }

        case 1: {
            //TODO: Edit authors.
            return false;
        }

        case 2: {
            pub->setYear(value.toInt());

            return true;
        }

        case 3: {
            pub->setJournal(value.toString());

            return true;
        }

        case 4: {
            pub->setConference(value.toString());

            return true;
        }
    }

    return false;
}

QString PublicationModel::formatAuthors(Author::List authors) const
{
    QStringList authorsList;

    foreach(Author::Ptr author, authors) {
        authorsList += (author->fullName());
    }

    return authorsList.join(", ");
}
