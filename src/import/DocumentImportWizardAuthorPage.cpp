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

#include "DocumentImportWizardAuthorPage.h"
#include "DocumentImportWizard.h"

#include <library/Repository.h>
#include <ui/AuthorEditWidget.h>

#include <KIcon>

DocumentImportWizardAuthorPage::DocumentImportWizardAuthorPage()
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

DocumentImportWizardAuthorPage::~DocumentImportWizardAuthorPage()
{
}

bool DocumentImportWizardAuthorPage::validatePage()
{
    QStringList authors = mEditWidget->currentAuthorList();
    DocumentImportWizard *wiz = static_cast<DocumentImportWizard *>(wizard());

    wiz->document()->setAuthors(authors);

    return true;
}

void DocumentImportWizardAuthorPage::initializePage()
{
    DocumentImportWizard *wiz = static_cast<DocumentImportWizard *>(wizard());

    mEditWidget->setLocalUrl(wiz->document()->localUrl());
    mEditWidget->setAuthorList(wiz->document()->authors());
}
