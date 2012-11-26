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

#ifndef DOCUMENTEXPORTER_H_
#define DOCUMENTEXPORTER_H_

#include <library/Publication.h>

#include <QByteArray>

/*! Interface for document exporters.
 *
 * Possible implementations of this interface should be able to export to some citation format (BibTex) or maybe to HTML.
 */
class DocumentExporter
{
    public:
        DocumentExporter();
        virtual ~DocumentExporter();

        /*! Exports a list of Documents and returns a QByteArray containing the contents of the export.
         */
        virtual QByteArray exportDocuments(const Publication::List &pubss) const = 0;
};

#endif /* DOCUMENTEXPORTER_H_ */
