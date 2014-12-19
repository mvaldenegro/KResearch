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

#ifndef INFOPANELHEADER_H_
#define INFOPANELELEMENT_H_

#include <QWidget>

#include "InfoPanelElementHeader.h"
#include "EditableLabel.h"

class InfoPanelElement : public QWidget
{
    Q_OBJECT

    public:
        InfoPanelElement(const QString& title, const QString& data, QWidget *parent = nullptr);
        virtual ~InfoPanelElement();

    signals:
        void elementEdited(const QString& title, const QString& data);

    public slots:
        void labelEdit(const QString& data);

    private:
        InfoPanelElementHeader *mHeader;
        EditableLabel *mDisplay;
};

#endif /* INFOPANELELEMENT_H_ */
