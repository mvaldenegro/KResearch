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

#ifndef INFOPANELDOCK_H_
#define INFOPANELDOCK_H_

#include <library/Document.h>

#include <QDockWidget>
#include <QVBoxLayout>

class QScrollArea;

class InfoPanelDock : public QDockWidget
{
    Q_OBJECT

    public:
        InfoPanelDock(QWidget *parent);
        virtual ~InfoPanelDock();

    public slots:
        void display(Document::Ptr document);
        void clear();

    private:
        QScrollArea *mScrollArea;
        QVBoxLayout *mLayout;

        void addElement(const QString& title, const QString& data);
};

#endif /* INFOPANELDOCK_H_ */
