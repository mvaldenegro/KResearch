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

#include "InfoPanelElement.h"

#include <QVBoxLayout>

InfoPanelElement::InfoPanelElement(const QString& title, const QString& data, QWidget *parent)
: QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);

    mHeader = new InfoPanelElementHeader();
    mHeader->setTitle(title);

    mDisplay = new EditableLabel();
    mDisplay->setText(data);

    layout->addWidget(mHeader);
    layout->addWidget(mDisplay);

    connect(mDisplay, SIGNAL(textEdited(const QString&)), this, SLOT(labelEdit(const QString&)));
}

InfoPanelElement::~InfoPanelElement()
{
}

void InfoPanelElement::labelEdit(const QString& data)
{
    emit elementEdited(mHeader->title(), data);
}
