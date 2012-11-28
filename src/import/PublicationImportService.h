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

#ifndef IMPORTSERVICE_H_
#define IMPORTSERVICE_H_

#include <QString>

#include <library/Document.h>

class DocumentDAO;

class PublicationImportService
{
    public:
        PublicationImportService(DocumentDAO *pubDAO);
        virtual ~PublicationImportService();

        bool import(const QString& fileName);

    protected:
        bool isAcceptedSuffix(const QString& suffix) const;

        DocumentDAO *publicationDAO() const
        {
            return mPubDAO;
        }

    private:
        DocumentDAO *mPubDAO;
};

#endif /* IMPORTSERVICE_H_ */
