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

#include "SQLiteJournalDAO.h"
#include <library/sqlite/SQLiteRepository.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

SQLiteJournalDAO::SQLiteJournalDAO(SQLiteRepository *cache)
: JournalDAO(), SQLiteBaseDAO(cache)
{
}

SQLiteJournalDAO::~SQLiteJournalDAO()
{
}

Journal::Ptr SQLiteJournalDAO::findById(qulonglong id) const
{
    if(repository()->journals()->contains(id)) {
        return repository()->journals()->find(id);
    }

    QSqlQuery query(database());
    bool ok = true;
    ok &= query.prepare("SELECT * FROM journal WHERE id = :id");
    query.bindValue(":id", id);
    ok &= query.exec();

    debug(query);

    if(ok) {

        if(query.next()) {

            QSqlRecord record = query.record();
            qulonglong id = record.value("id").toULongLong();
            Journal::Ptr journal = Journal::Ptr(new Journal());

            journal->setId(id);
            journal->setName(record.value("name").toString());
            journal->setPublisher(record.value("publisher").toString());
            journal->setUrl(record.value("url").toString());
            journal->setJournalPolicy(JournalPolicy::fromUInt(record.value("policy").toUInt()));

            repository()->journals()->insert(id, journal);

            emit dataChanged();

            return journal;
        }

    }

    return Journal::Ptr();
}

Journal::Ptr SQLiteJournalDAO::findByName(const QString& name) const
{
    QSqlQuery query(database());
    bool ok = true;
    ok &= query.prepare("SELECT id FROM journal WHERE name = :name");
    query.bindValue(":name", name);
    ok &= query.exec();

    debug(query);

    if(ok && query.next()) {
        return findById(query.record().value("id").toULongLong());
    }

    return Journal::Ptr(0);
}

bool SQLiteJournalDAO::saveOrUpdate(Journal::Ptr journal)
{
    if(!journal) {
        return false;
    }

    const qulonglong invalidId = (qulonglong) -1;

    if(journal->id() == invalidId) {

        return save(journal);
    } else {

        return update(journal);
    }
}

Journal::List SQLiteJournalDAO::findAll() const
{
    return repository()->journals()->findAll();
}

bool SQLiteJournalDAO::save(Journal::Ptr journal)
{
    if(!journal) {
        return false;
    }

    bool ok = true;
    database().transaction();

    qDebug() << "Transaciton ok?" << ok;

    QSqlQuery query(database());
    ok &= query.prepare("INSERT INTO journal(name, publisher, url, policy) "
                        "VALUES(:name, :publisher, :url, :policy)");

    qDebug() << "Prepare ok?" << ok;

    query.bindValue(":name", journal->name());
    query.bindValue(":publisher", journal->publisher());
    query.bindValue(":url", journal->url());
    query.bindValue(":policy", journal->journalPolicy().toUInt());
    ok &= query.exec();

    qDebug() << "Query ok?" << ok;

    debug(query);

    if(ok) {
        qulonglong id = lastInsertRowID();
        journal->setId(id);

        repository()->journals()->insert(id, journal);
    } else {
        qDebug() << "Query failed!?";
    }

    if(!ok) {
        ok &= database().rollback();
    } else {
        ok &= database().commit();
    }

    emit dataChanged();

    return ok;
}

bool SQLiteJournalDAO::update(Journal::Ptr journal)
{
    if(!journal) {
        return false;
    }

    bool ok = true;

    QSqlQuery query(database());
    ok &= query.prepare("UPDATE journal SET name = :name, publisher = :publisher, url = :url,"
                        " policy = :policy "
                        "WHERE id = :id");

    query.bindValue(":id", journal->id());
    query.bindValue(":name", journal->name());
    query.bindValue(":publisher", journal->publisher());
    query.bindValue(":url", journal->url());
    query.bindValue(":policy", journal->journalPolicy().toUInt());
    ok &= query.exec();

    debug(query);

    emit dataChanged();

    return ok;
}

QStringList SQLiteJournalDAO::journalNames() const
{
    QStringList ret;
    Journal::List journals = findAll();

    foreach(Journal::Ptr journal, journals) {
        ret += journal->name();
    }

    return ret;
}
