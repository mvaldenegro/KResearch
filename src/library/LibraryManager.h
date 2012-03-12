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

#ifndef LIBRARYMANAGER_H_
#define LIBRARYMANAGER_H_

#include <QSqlDatabase>
#include <QString>

class Repository;

class LibraryManager
{
    public:
        LibraryManager();
        virtual ~LibraryManager();

        Repository *repository() const
        {
            return mLibraryRepository;
        }

        QString databaseFile() const
        {
            return mLibraryPath + '/' + mLibraryDatabaseFilename;
        }

        QString libraryPath() const
        {
            return mLibraryPath;
        }

        static LibraryManager *self()
        {
            return mInstance;
        }

    protected:
        void init();
        void shutdown();

        bool openDatabase();
        bool createDatabase();
        bool checkDatabase();
        bool loadDatabase();

        void saveConfig();
        void loadConfig();

    private:
        QString mLibraryPath;
        QString mLibraryDatabaseFilename;

        Repository *mLibraryRepository;
        QSqlDatabase mLibraryDatabase;

        static LibraryManager *mInstance;
};

#endif /* LIBRARYMANAGER_H_ */
