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

    mCurrentRow = 0;
}

InformationDockWidget::~InformationDockWidget()
{
}

void InformationDockWidget::display(Document::Ptr pub)
{
    if(pub) {
        qDebug() << pub->title() << "selected";

        mWidgetUi->titleLabel->setText(pub->title());
        mWidgetUi->authorsLabel->setText(pub->authorNames().join(", "));
        mWidgetUi->abstractLabel->setText(pub->abstract());

        clear();

        int row = 0;

        if(pub->journal()) {
            Journal::Ptr journal = pub->journal();

            if(!journal->name().isEmpty()) {
                displayMetadata("Journal:", journal->name());
            }

            if(!journal->series().isEmpty()) {
                displayMetadata("Series:", journal->series());
            }

            if(!journal->subseries().isEmpty()) {
                displayMetadata("Subseries:", journal->subseries());
            }
        }

        if(!pub->conference().isEmpty()) {
            displayMetadata("Conference:", pub->conference());
        }

        if(!pub->publisher().isEmpty()) {
            displayMetadata("Published by:", pub->publisher());
        }

        if(pub->volume() > 0) {
            displayMetadata("Volume:", QString::number(pub->volume()));
        }

        if(pub->number() > 0) {
            displayMetadata("Number:", QString::number(pub->number()));
        }

        if(!pub->url().isEmpty()) {
            displayMetadata("URL:", pub->url());
        }

        if(!pub->doi().isEmpty()) {
            displayMetadata("DOI:", pub->doi());
        }

        if(!pub->isbn().isEmpty()) {
            displayMetadata("ISBN:", pub->isbn());
        }
    }
}

void InformationDockWidget::displayMetadata(const QString& title, const QString& contents)
{
    mWidgetUi->metadataGridLayout->addWidget(label(title), mCurrentRow, 0, Qt::AlignRight);
    mWidgetUi->metadataGridLayout->addWidget(label(contents), mCurrentRow, 1);

    mCurrentRow++;
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

    mCurrentRow = 0;
}
