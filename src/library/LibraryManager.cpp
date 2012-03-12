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

#include "LibraryManager.h"
#include "DatabaseSchema.h"

#include <sqliteLibrary/SQLiteRepository.h>

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QFile>

#include <KFileDialog>
#include <KGlobal>
#include <KConfig>
#include <KConfigGroup>

LibraryManager *LibraryManager::mInstance = 0;

LibraryManager::LibraryManager()
: mLibraryPath(), mLibraryRepository(0)
{
    init();

    mInstance = this;
}

LibraryManager::~LibraryManager()
{
    shutdown();
}

void LibraryManager::init()
{
    qDebug("LibraryManager: init");

    loadConfig();

    if(libraryPath().isEmpty() || !QDir(libraryPath()).exists()) {

        mLibraryPath = KFileDialog::getExistingDirectory(KUrl(), 0, "Please select a folder for your research library.");
    }

    if(!QFile::exists(databaseFile())) {
        createDatabase();
    }

    checkDatabase();
    loadDatabase();

    mLibraryRepository = new SQLiteRepository(mLibraryDatabase);
}

void LibraryManager::shutdown()
{
    qDebug("LibraryManager: shutdown");

    saveConfig();

    mLibraryDatabase.close();
}

bool LibraryManager::openDatabase()
{
    if(!QSqlDatabase::isDriverAvailable("QSQLITE")) {

        qDebug("LibraryManager: QSQLITE driver is not available!");

        return false;
    }

    bool ok = true;

    if(!mLibraryDatabase.isOpen()) {

        mLibraryDatabase = QSqlDatabase::addDatabase("QSQLITE");
        mLibraryDatabase.setDatabaseName(databaseFile());

        ok = mLibraryDatabase.open();
    }

    return ok;
}

bool LibraryManager::createDatabase()
{
    qDebug("LibraryManager: Database does NOT exist, creating.");

    bool ok = openDatabase();

    if(!ok) {

        qDebug("LibraryManager: Can't open database file %s", databaseFile().toLatin1().data());

        return false;
    }

    ok = true;

    QStringList schemas = databaseSchema();
    QSqlQuery query(mLibraryDatabase);

    foreach(QString schema, schemas) {
        ok &= query.exec(schema);
    }

    if(ok) {
        qDebug("LibraryManager: Database creation OK");

    } else {
        qDebug("LibraryManager: Database creation ERROR");

        QSqlError error = query.lastError();

        if(error.isValid()) {
            qDebug("LibraryManager: %s", error.text().toLatin1().data());
        }
    }

    return ok;
}

bool LibraryManager::checkDatabase()
{
    return true;
}

bool LibraryManager::loadDatabase()
{
    qDebug("LibraryManager: Loading database");

    bool ok =  openDatabase();

    if(ok) {
        qDebug("LibraryManager: Database loaded successfully");
    } else {
        qDebug("LibraryManager: Database could not be loaded.");
    }

    return ok;
}

void LibraryManager::saveConfig()
{
    KSharedConfigPtr config = KGlobal::config();

    config->group("library").writeEntry("databaseFile", mLibraryDatabaseFilename);
    config->group("library").writeEntry("libraryPath", mLibraryPath);

    config->sync();
}

void LibraryManager::loadConfig()
{
    KSharedConfigPtr config = KGlobal::config();

    mLibraryDatabaseFilename = config->group("library").readEntry("databaseFile", QString("library.sqlite"));
    mLibraryPath = config->group("library").readEntry("libraryPath", QString());
}
