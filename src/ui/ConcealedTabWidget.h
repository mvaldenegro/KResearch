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

#ifndef CONCEALEDTABWIDGET_H_
#define CONCEALEDTABWIDGET_H_

#include <KTabWidget>

class ConcealedTabWidget : public KTabWidget
{
    public:
        ConcealedTabWidget(QWidget *parent = 0);
        virtual ~ConcealedTabWidget();

    protected:

        virtual void tabInserted(int index);
        virtual void tabRemoved(int index);

};

#endif /* CONCEALEDTABWIDGET_H_ */
