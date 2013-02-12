#ifndef DATABASE_SCHEMA_H_
#define DATABASE_SCHEMA_H_

#include <QString>
#include <QStringList>

QStringList databaseSchema()
{
    QStringList ret;

    ret << QString("CREATE TABLE IF NOT EXISTS author (\n"
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                   "firstName TEXT NOT NULL,\n"
                   "lastName TEXT NOT NULL,\n"
                   "emailAddress TEXT,\n"
                   "affiliation TEXT,\n"
                   "UNIQUE(firstName, lastName)\n"
                   ");");

    ret << QString("CREATE TABLE IF NOT EXISTS journal (\n"
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                   "name TEXT NOT NULL UNIQUE,\n"
                   "publisher TEXT,\n"
                   "series TEXT,\n"
                   "subseries TEXT,\n"
                   "url TEXT,\n"
                   "policy INTEGER\n"
                   ");");

    ret << QString("CREATE TABLE IF NOT EXISTS publication (\n"
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,\n"
                   "title TEXT NOT NULL,\n"
                   "abstract TEXT,\n"
                   "year INTEGER,\n"
                   "conference TEXT,\n"
                   "publisher TEXT,\n"
                   "volume INTEGER,\n"
                   "number INTEGER,\n"
                   "url TEXT,\n"
                   "doi TEXT,\n"
                   "isbn TEXT,\n"
                   "localURL TEXT,\n"
                   "isPublished BOOLEAN,\n"
                   "isPeerReviewed BOOLEAN,\n"
                   "type INTEGER,\n"
                   "journalId INTEGER,\n"
                   "series TEXT,\n"
                   "subTitle TEXT,\n"
                   "pages TEXT,\n"
                   "authors TEXT,\n"
                   "editors TEXT,\n"
                   "FOREIGN KEY(journalId) references journal(id)\n"
                   ");");

    return ret;
}

#endif /* DATABASE_SCHEMA_H */
