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

#ifndef JOURNALPOLICY_H_
#define JOURNALPOLICY_H_

#include <library/TypedEnum.h>

class JP
{
    public:
        enum Type
        {
            Unknown = 0,
            OpenAccess,
            ClosedAccess
        };

        static QHash<unsigned int, QString> toStringHash()
        {
            QHash<unsigned int, QString> ret;

            ret[Unknown] = "Unknown";
            ret[OpenAccess] = "Open Access";
            ret[ClosedAccess] = "Closed Access";

            return ret;
        }
};

typedef TypedEnum<JP> JournalPolicy;

#endif /* JOURNALPOLICY_H_ */
