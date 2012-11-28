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
 * along with Epic Framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "JournalModel.h"

#include <QDebug>
#include <QVariant>
#include <library/dao/DocumentDAO.h>

JournalModel::JournalModel(DocumentDAO *pubDAO)
 : QAbstractItemModel(), mPublicationDAO(pubDAO)
{
}

JournalModel::~JournalModel()
{
}

int JournalModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return 2;
}

int JournalModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    int ret  = mPublicationDAO->journals().length();

    qDebug() << "How many journals?" << ret;

    return ret;
}
QVariant JournalModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    int i = index.row();
    int j = index.column();

    if(i < 0 || i > mPublicationDAO->journals().count()) {
        return QVariant();
    }

    if(role == Qt::DisplayRole) {
        return handleRead(i, j);
    }

    return QVariant();
}

QVariant JournalModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal) {
        return QVariant();
    }

    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    return handleColumnNames(section);
}

QModelIndex JournalModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    //TODO: Use the internalId to do indexing into the DAO.
    return createIndex(row, column, (void *) 0);
}

QModelIndex JournalModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

Qt::ItemFlags JournalModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)

    return Qt::ItemIsEnabled;
}

QVariant JournalModel::handleColumnNames(int column) const
{
    switch(column) {
        case 0: {
            return "Journal name";
        }

        case 1: {
            return "Publication count";
        }
    }

    return QVariant();
}

QVariant JournalModel::handleRead(int row, int column) const
{
    switch(column) {
        case 0: {
            QString ret = mPublicationDAO->journals().at(row);

            qDebug() << "Returning" << ret;

            return ret;
        }

        case 1: {
            return 10;
        }
    }

    return QVariant();
}
