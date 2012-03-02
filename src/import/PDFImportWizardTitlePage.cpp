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

#include "PDFImportWizardTitlePage.h"
#include "PDFImportWizard.h"
#include <pdfwidget/PDFDocumentDialog.h>

PDFImportWizardTitlePage::PDFImportWizardTitlePage()
: QWizardPage()
{
    setTitle("Publication information");
    setSubTitle("Please enter the required information about this publication");

    setupUi(this);

    registerField("title*", titleEdit);
    registerField("year", yearEdit);
    registerField("journal", journalEdit);
    registerField("conference", conferenceEdit);

    connect(titleButton, SIGNAL(clicked()), this, SLOT(acquireTitle()));
    connect(yearButton, SIGNAL(clicked()), this, SLOT(acquireYear()));
    connect(journalButton, SIGNAL(clicked()), this, SLOT(acquireJournal()));
    connect(conferenceButton, SIGNAL(clicked()), this, SLOT(acquireConference()));
}

PDFImportWizardTitlePage::~PDFImportWizardTitlePage()
{
}

void PDFImportWizardTitlePage::acquireTitle()
{
    PDFImportWizard *wiz = static_cast<PDFImportWizard *>(wizard());

    QString title = PDFDocumentDialog::selectString(wiz->publication()->localUrl());
    setField("title", title.simplified());
}
void PDFImportWizardTitlePage::acquireYear()
{
    PDFImportWizard *wiz = static_cast<PDFImportWizard *>(wizard());

    QString year = PDFDocumentDialog::selectString(wiz->publication()->localUrl());
    setField("year", year.simplified());
}

void PDFImportWizardTitlePage::acquireJournal()
{
    PDFImportWizard *wiz = static_cast<PDFImportWizard *>(wizard());

    QString journal = PDFDocumentDialog::selectString(wiz->publication()->localUrl());
    setField("journal", journal.simplified());
}

void PDFImportWizardTitlePage::acquireConference()
{
    PDFImportWizard *wiz = static_cast<PDFImportWizard *>(wizard());

    QString conference = PDFDocumentDialog::selectString(wiz->publication()->localUrl());
    setField("conference", conference.simplified());

}
