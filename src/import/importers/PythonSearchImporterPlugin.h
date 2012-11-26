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

#ifndef PYTHONSEARCHIMPORTERPLUGIN_H_
#define PYTHONSEARCHIMPORTERPLUGIN_H_

#include <import/importers/OnlineSearchImporter.h>

#include <Kross/Interpreter>

/*! This is the online importer interface, but specialized for a implementation as a Python script.
 *
 */
class PythonSearchImporterPlugin : public OnlineSearchImporter
{
    public:
        PythonSearchImporterPlugin();
        virtual ~PythonSearchImporterPlugin();

        virtual Publication::List search(const QStringList& keywords) const;
};

#endif /* PYTHONSEARCHIMPORTERPLUGIN_H_ */
