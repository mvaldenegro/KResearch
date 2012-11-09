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

#ifndef INFORMATIONDOCKWIDGET_H_
#define INFORMATIONDOCKWIDGET_H_

#include <QDockWidget>

#include <library/Publication.h>

#include "ui_PublicationInformation.h"

class QScrollArea;

class InformationDockWidget : public QDockWidget
{
    Q_OBJECT

    public:
        InformationDockWidget(QWidget *parent);
        virtual ~InformationDockWidget();

    public Q_SLOTS:
        void display(Publication::Ptr pub);
        void displayMetadata(const QString& title, const QString& content);

    protected:
        QLabel *label(const QString& contents) const;
        void clear();

    private:
        QScrollArea *mScrollArea;
        QWidget *mWidget;
        Ui::PublicationInformation *mWidgetUi;

        size_t mCurrentRow;
};

#endif /* INFORMATIONDOCKWIDGET_H_ */
