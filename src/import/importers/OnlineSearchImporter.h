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

#ifndef ONLINESEARCHIMPORTER_H_
#define ONLINESEARCHIMPORTER_H_

#include <library/Document.h>
#include <QStringList>

/*! This is a importer interface for online search engines, such as Google Scholar, Citeseer, and
 * other online publication sites, like Journals and aggregators.
 *
 */
class OnlineSearchImporter
{
    public:
        OnlineSearchImporter();
        virtual ~OnlineSearchImporter();

        /*! Search this importer for a list of keywords, and returns a list of documents that match the keywords.
         *
         */
        virtual Document::List search(const QStringList& keywords) const = 0;
};

#endif /* ONLINESEARCHIMPORTER_H_ */
