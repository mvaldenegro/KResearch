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

#include "PDFImportWizardAuthorPage.h"
#include "PDFImportWizard.h"

#include <library/Repository.h>
#include <ui/AuthorEditWidget.h>

#include <KIcon>

PDFImportWizardAuthorPage::PDFImportWizardAuthorPage()
: QWizardPage()
{
    setTitle("Publication authors");
    setSubTitle("Please enter the authors of this publication");

    setupUi(this);

    addAuthorButton->setIcon(KIcon("list-add"));
    removeAuthorButton->setIcon(KIcon("list-remove"));

    QVBoxLayout *authorEditLayout = new QVBoxLayout(authorEditWidget);
    mEditWidget = new AuthorEditWidget(authorEditWidget);

    authorEditLayout->addWidget(mEditWidget);
    authorEditLayout->setSpacing(0);
    authorEditLayout->setMargin(0);
    authorEditLayout->setContentsMargins(0, 0, 0, 0);

    connect(authorButton, SIGNAL(clicked()), mEditWidget, SLOT(acquireAuthor()));
    connect(addAuthorButton, SIGNAL(clicked()), mEditWidget, SLOT(addAuthor()));
    connect(removeAuthorButton, SIGNAL(clicked()), mEditWidget, SLOT(removeSelectedAuthor()));
}

PDFImportWizardAuthorPage::~PDFImportWizardAuthorPage()
{
}

bool PDFImportWizardAuthorPage::validatePage()
{
    QStringList authors = mEditWidget->currentAuthorList();
    Author::List authList;

    foreach(QString authorStr, authors) {

        QStringList parts = authorStr.split(',');
        QString lastName = parts[0].trimmed();
        QString firstName = parts[1].trimmed();

        Author::Ptr candidate = Repository::self()->authorDAO()->findByFullName(firstName, lastName);

        if(!candidate) {

            candidate = new Author();

            candidate->setFirstName(firstName);
            candidate->setLastName(lastName);
        }

        authList.append(candidate);
    }

    PDFImportWizard *wiz = static_cast<PDFImportWizard *>(wizard());

    wiz->publication()->setAuthors(authList);

    return true;
}

void PDFImportWizardAuthorPage::initializePage()
{
    PDFImportWizard *wiz = static_cast<PDFImportWizard *>(wizard());

    mEditWidget->setLocalUrl(wiz->publication()->localUrl());
}
