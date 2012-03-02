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

#include "PDFDocumentDialog.h"

#include <QObject>
#include <QDialog>
#include <QDebug>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "PDFDocumentWidget.h"

PDFDocumentDialog::PDFDocumentDialog()
 : QDialog()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *okLayout = new QHBoxLayout();

    mDocWidget = new PDFDocumentWidget(this);
    mOKButton = new QPushButton(this);
    mOKButton->setText("Accept");

    layout->addWidget(mDocWidget);
    layout->addLayout(okLayout);

    okLayout->addStretch(10);
    okLayout->addWidget(mOKButton);

    connect(mOKButton, SIGNAL(clicked()), this, SLOT(accept()));
}

PDFDocumentDialog::~PDFDocumentDialog()
{
}

SignalCatcher::SignalCatcher()
 : QObject()
{
}

SignalCatcher::~SignalCatcher()
{
}

void SignalCatcher::catchString(const QString& str)
{
    mCatchedString = str;

    qDebug() << "Catched" << str;
}

QString PDFDocumentDialog::selectString(const QString& fileName)
{
    PDFDocumentDialog dialog;
    SignalCatcher catcher;

    QObject::connect(dialog.mDocWidget, SIGNAL(textSelected(const QString&)), &catcher, SLOT(catchString(const QString&)));

    dialog.mDocWidget->setDocument(fileName);

    dialog.setModal(true);
    dialog.showNormal();
    dialog.exec();

    return catcher.catchedString();
}
