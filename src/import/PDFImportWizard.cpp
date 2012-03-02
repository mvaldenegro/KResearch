/*
 * Copyright (C) 2011-2012 Matias Valdenegro <matias.valdenegro@gmail.com>
 * This file is part of kresearch.
 *
 * kresearch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * kresearch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with kresearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PDFImportWizard.h"
#include "PDFImportWizardTitlePage.h"
#include "PDFImportWizardAuthorPage.h"

PDFImportWizard::PDFImportWizard(Publication::Ptr pub)
: QWizard()
{
    addPage(new PDFImportWizardTitlePage());
    addPage(new PDFImportWizardAuthorPage());

    setField("title", pub->title());
    setField("year", pub->year());
    setField("journal", pub->journal());
    setField("conference", pub->conference());

    mPub = pub;

    setWindowTitle("Publication import wizard");
}

PDFImportWizard::~PDFImportWizard()
{
}

bool PDFImportWizard::importPublication(Publication::Ptr pub)
{
    PDFImportWizard wizard(pub);
    int exec = wizard.exec();

    if(exec == QDialog::Accepted) {

        QString title = wizard.field("title").toString();
        int year = wizard.field("year").toInt();
        QString journal = wizard.field("journal").toString();
        QString conference = wizard.field("conference").toString();

        pub->setTitle(title);
        pub->setYear(year);
        pub->setJournal(journal);
        pub->setConference(conference);

        return true;
    }

    return false;
}
