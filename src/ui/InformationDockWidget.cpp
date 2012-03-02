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

#include "InformationDockWidget.h"

#include <QScrollArea>
#include <QDebug>

InformationDockWidget::InformationDockWidget(QWidget *parent)
 : QDockWidget("Information", parent)
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setObjectName("informationDockWidget");

    mScrollArea = new QScrollArea();

    mWidget = new QWidget();
    mWidgetUi = new Ui::PublicationInformation();

    mWidgetUi->setupUi(mWidget);

    mWidgetUi->titleLabel->setWordWrap(true);
    mWidgetUi->authorsLabel->setWordWrap(true);
    mWidgetUi->abstractLabel->setWordWrap(true);

    mScrollArea->setWidget(mWidget);
    mScrollArea->setWidgetResizable(true);

    setWidget(mScrollArea);
}

InformationDockWidget::~InformationDockWidget()
{
}

void InformationDockWidget::display(Publication::Ptr pub)
{
    if(pub) {
        qDebug() << pub->title() << "selected";

        mWidgetUi->titleLabel->setText(pub->title());
        mWidgetUi->authorsLabel->setText(pub->authorNames().join(", "));
        mWidgetUi->abstractLabel->setText(pub->abstract());

        clear();

        int row = 0;

        if(!pub->journal().isEmpty()) {

            mWidgetUi->metadataGridLayout->addWidget(label("Journal:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->journal()), row, 1);

            row++;
        }

        if(!pub->conference().isEmpty()) {

            mWidgetUi->metadataGridLayout->addWidget(label("Conference: "), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->conference()), row, 1);

            row++;
        }

        if(!pub->publisher().isEmpty()) {

            mWidgetUi->metadataGridLayout->addWidget(label("Published by:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->publisher()), row, 1);

            row++;
        }

        if(!pub->series().isEmpty()) {
            mWidgetUi->metadataGridLayout->addWidget(label("Series:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->series()), row, 1);

            row++;
        }

        if(!pub->subseries().isEmpty()) {
            mWidgetUi->metadataGridLayout->addWidget(label("Subseries:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->subseries()), row, 1);

            row++;
        }

        if(pub->volume() > 0) {
            mWidgetUi->metadataGridLayout->addWidget(label("Volume:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(QString::number(pub->number())), row, 1);

            row++;
        }

        if(pub->number() > 0) {
            mWidgetUi->metadataGridLayout->addWidget(label("Number:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(QString::number(pub->number())), row, 1);

            row++;
        }

        if(!pub->url().isEmpty()) {
            mWidgetUi->metadataGridLayout->addWidget(label("URL:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->url()), row, 1);

            row++;
        }

        if(!pub->doi().isEmpty()) {
            mWidgetUi->metadataGridLayout->addWidget(label("DOI:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->doi()), row, 1);

            row++;
        }

        if(!pub->isbn().isEmpty()) {
            mWidgetUi->metadataGridLayout->addWidget(label("ISBN:"), row, 0, Qt::AlignRight);
            mWidgetUi->metadataGridLayout->addWidget(label(pub->isbn()), row, 1);

            row++;
        }
    }
}

QLabel *InformationDockWidget::label(const QString& contents) const
{
    QLabel *label = new QLabel(contents);

    label->setWordWrap(true);

    return label;
}

void InformationDockWidget::clear()
{
    for(int row = 0; row < mWidgetUi->metadataGridLayout->rowCount(); row++) {
        for(int col = 0; col < mWidgetUi->metadataGridLayout->columnCount(); col++) {

            QLayoutItem *item = mWidgetUi->metadataGridLayout->itemAtPosition(row, col);

            if(item) {
                mWidgetUi->metadataGridLayout->removeItem(item);

                delete item->widget();
                delete item;
            }
        }
    }
}
