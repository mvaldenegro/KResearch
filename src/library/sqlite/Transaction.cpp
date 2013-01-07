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

#include "Transaction.h"

#include <QDebug>

Transaction::InternalTransactionState *Transaction::mCurrentTransactionState = 0;

Transaction::Transaction(QSqlDatabase database)
{
    if(!currentTransaction()) {
        mCurrentTransactionState = new InternalTransactionState();
        mCurrentTransactionState->referenceCount = 0;
        mCurrentTransactionState->database = database;

        bool ret = currentTransaction()->database.transaction();

        qDebug() << "Starting transaction. Status = " << ret;
    }

    currentTransaction()->referenceCount++;

    qDebug() << "Transaction reference count" << currentTransaction()->referenceCount;
}

Transaction::~Transaction()
{
    commit();
}

bool Transaction::commit()
{
    if(currentTransaction()) {
        currentTransaction()->referenceCount--;

        qDebug() << "Transaction reference count" << currentTransaction()->referenceCount;

        if(currentTransaction()->referenceCount == 0) {
            bool ret = currentTransaction()->database.commit();

            delete mCurrentTransactionState;
            mCurrentTransactionState = 0;

            qDebug() << "Committing transaction. Status = " << ret;

            return ret;
        }
    }

    return false;
}

bool Transaction::rollback()
{
    if(currentTransaction()) {
        bool ret = currentTransaction()->database.rollback();

        delete mCurrentTransactionState;
        mCurrentTransactionState = 0;

        qDebug() << "Rollbacking transaction. Status = " << ret;

        return ret;
    }

    return false;
}
