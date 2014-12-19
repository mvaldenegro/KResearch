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

#include "InfoPanelDock.h"
#include "InfoPanelElement.h"

#include <QScrollArea>
#include <QDebug>

InfoPanelDock::InfoPanelDock(QWidget *parent)
: QDockWidget("Information", parent)
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setObjectName("informationDockWidget");

    mScrollArea = new QScrollArea();
    QWidget *area = new QWidget();
    mLayout = new QVBoxLayout();
    area->setLayout(mLayout);
    mScrollArea->setWidget(area);
    mScrollArea->setWidgetResizable(true);

    setWidget(mScrollArea);
    area->setStyleSheet("QWidget { background-color: white }");
    QPalette p = area->palette();
    p.setColor(QPalette::Window, QColor("white"));
    area->setPalette(p);

    display(new Document());
}

InfoPanelDock::~InfoPanelDock()
{
}

void InfoPanelDock::display(Document::Ptr document)
{
    if(!document) {
        return;
    }

    clear();

    qDebug() << "Showing document";

    addElement("Title", document->title());
    addElement("Authors", document->authors().join(", "));

    mLayout->addStretch();
}

void InfoPanelDock::clear()
{
    while(true) {
        QLayoutItem *item = mLayout->itemAt(0);

        if(item) {
            mLayout->removeItem(item);

            delete item->widget();
            delete item;
        } else {
            break;
        }
    }
}


void InfoPanelDock::addElement(const QString& title, const QString& data)
{
    InfoPanelElement *element = new InfoPanelElement(title, data);

    mLayout->addWidget(element);
}
