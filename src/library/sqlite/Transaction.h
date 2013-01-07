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

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <QSqlDatabase>

class Transaction
{
    public:
        Transaction(QSqlDatabase database = QSqlDatabase::database());
        virtual ~Transaction();

        bool commit();
        bool rollback();

    private:

        struct InternalTransactionState
        {
            unsigned int referenceCount;
            QSqlDatabase database;
        };

        static InternalTransactionState *currentTransaction()
        {
            return mCurrentTransactionState;
        }

        static InternalTransactionState *mCurrentTransactionState;
};

#endif /* TRANSACTION_H_ */
