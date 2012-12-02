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

#include "DocumentImportWizard.h"
#include "DocumentImportWizardTitlePage.h"
#include "DocumentImportWizardAuthorPage.h"

#include <library/Repository.h>
#include <library/dao/JournalDAO.h>

DocumentImportWizard::DocumentImportWizard(Document::Ptr pub)
: QWizard()
{
    addPage(new DocumentImportWizardTitlePage());
    addPage(new DocumentImportWizardAuthorPage());

    setField("title", pub->title());
    setField("year", pub->year());

    if(pub->journal()) {
        setField("journal", pub->journal()->name());
    } else {
        setField("journal", QString());
    }

    setField("conference", pub->conference());

    mPub = pub;

    setWindowTitle("Publication import wizard");
}

DocumentImportWizard::~DocumentImportWizard()
{
}

bool DocumentImportWizard::importDocument(Document::Ptr doc)
{
    DocumentImportWizard wizard(doc);

    if(wizard.exec() == QDialog::Accepted) {

        QString title = wizard.field("title").toString();
        int year = wizard.field("year").toInt();
        QString journal = wizard.field("journal").toString();
        QString conference = wizard.field("conference").toString();

        JournalDAO *journalDAO = Repository::self()->journalDAO();

        doc->setTitle(title);
        doc->setYear(year);
        doc->setJournal(journalDAO->findByName(journal));
        doc->setConference(conference);

        return true;
    }

    return false;
}
