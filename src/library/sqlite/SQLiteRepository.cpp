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

#include "SQLiteRepository.h"

#include <QVariant>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

#include "SQLiteAuthorDAO.h"
#include "SQLiteDocumentDAO.h"
#include "SQLiteJournalDAO.h"

static IDList allIDs(QSqlDatabase db, const QString& tableName)
{
    IDList ret;
    QSqlQuery query(QString("SELECT id FROM %1").arg(tableName), db);

    while(query.next()) {
        ret.append(query.record().value("id").toULongLong());
    }

    return ret;
}

SQLiteRepository::SQLiteRepository(QSqlDatabase db)
: mDB(db)
{
    mAuthorDAO = new SQLiteAuthorDAO(this);
    mPublicationDAO = new SQLiteDocumentDAO(this);
    mJournalDAO = new SQLiteJournalDAO(this);

    populate();
}

SQLiteRepository::~SQLiteRepository()
{
}

void SQLiteRepository::populate()
{
    IDList authors = allIDs(database(), "author");

    foreach(qulonglong aid, authors) {
        authorDAO()->findById(aid);
    }

    IDList pubs = allIDs(database(), "document");

    foreach(qulonglong pid, pubs) {
        publicationDAO()->findById(pid);
    }

    IDList journals = allIDs(database(), "journal");

    foreach(qulonglong jid, journals) {
        journalDAO()->findById(jid);
    }

    qDebug() << "Repository: loaded" << authors.count() << "Authors";
    qDebug() << "Repository: loaded" << pubs.count() << "Publications";
    qDebug() << "Repository: loaded" << journals.count() << "Journals";
}
