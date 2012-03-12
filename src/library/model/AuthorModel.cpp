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

#include "AuthorModel.h"

AuthorModel::AuthorModel(AuthorDAO *authorDAO)
 : QAbstractItemModel(), mAuthorDAO(authorDAO)
{
    connect(authorDAO, SIGNAL(dataChanged()), this, SLOT(invalidateData()));
}

AuthorModel::~AuthorModel()
{
}

int AuthorModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return 5;
}

int AuthorModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return mAuthorDAO->findAll().count();
}
QVariant AuthorModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }

    int i = index.row();
    int j = index.column();

    if(i < 0 || i > mAuthorDAO->findAll().count()) {
        return QVariant();
    }

    Author::Ptr pub = mAuthorDAO->findAll().at(index.row());

    if(role == Qt::DisplayRole) {
        return handleRead(pub, j);
    }

    if(role == Qt::EditRole) {
        return handleRead(pub, j);
    }

    return QVariant();
}

bool AuthorModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(index.isValid() && role == Qt::EditRole) {

        Author::Ptr pub = mAuthorDAO->findAll().at(index.row());
        bool ok = handleWrite(pub, value, index.column());

        if(ok) {
            emit dataChanged(index, index);

            mAuthorDAO->saveOrUpdate(pub);
        }

        return ok;
    }

    return false;
}

QVariant AuthorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal) {
        return QVariant();
    }

    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    return handleColumnNames(section);
}

QModelIndex AuthorModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    //TODO: Use the internalId to do indexing into the DAO.
    return createIndex(row, column, (void *) 0);
}

QModelIndex AuthorModel::parent(const QModelIndex& index) const
{
    Q_UNUSED(index);

    return QModelIndex();
}

Qt::ItemFlags AuthorModel::flags(const QModelIndex &index) const
{
    Q_UNUSED(index)

    if(index.column() == 2) {
        return Qt::ItemIsEnabled;
    }

    return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void AuthorModel::invalidateData()
{
    beginResetModel();
    endResetModel();
}

QVariant AuthorModel::handleColumnNames(int column) const
{
    switch(column) {
        case 0: {
            return "First name";
        }

        case 1: {
            return "Last name";
        }

        case 2: {
            return "Initials";
        }

        case 3: {
            return "Email Address";
        }

        case 4: {
            return "Affiliation";
        }
    }

    return QVariant();
}

QVariant AuthorModel::handleRead(Author::Ptr author, int column) const
{
    switch(column) {
        case 0: {
            return author->firstName();
        }

        case 1: {
            return author->lastName();
        }

        case 2: {
            return QString(author->firstName().at(0)) + QString(author->lastName().at(0));
        }

        case 3: {
            return author->emailAddress();
        }

        case 4: {
            return author->affiliation();
        }
    }

    return QVariant();
}

bool AuthorModel::handleWrite(Author::Ptr author, const QVariant& value, int column)
{
    switch(column) {
        case 0: {
            author->setFirstName(value.toString());

            return true;
        }

        case 1: {

            author->setLastName(value.toString());

            return true;
        }

        case 2: {

            // Can't edit initials.
            return false;
        }

        case 3: {
            author->setEmailAddress(value.toString());

            return true;
        }

        case 4: {
            author->setAffiliation(value.toString());

            return true;
        }
    }

    return false;
}
