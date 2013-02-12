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

#include "AuthorEditWidget.h"

#include <library/Repository.h>
#include <pdfwidget/PDFDocumentDialog.h>

#include <QListWidget>

AuthorEditWidget::AuthorEditWidget(QWidget *parent)
 : QWidget(parent)
{
    setupUi(this);

    authorList->setSelectionMode(QAbstractItemView::SingleSelection);
    authorList->setSelectionBehavior(QAbstractItemView::SelectItems);
    authorList->setSortingEnabled(true);

    QStringList authorNames = Repository::self()->authorDAO()->authorNames();

    authorComboBox->completionObject()->insertItems(authorNames);
    authorComboBox->setContextMenuEnabled(true);
}

AuthorEditWidget::~AuthorEditWidget()
{
}

void AuthorEditWidget::setAuthorList(const QStringList& authors)
{
    for(QString author: authors) {
        new QListWidgetItem(author, authorList);
    }
}

void AuthorEditWidget::setLocalUrl(const QString& localUrl)
{
    mLocalUrl = localUrl;
}

QStringList AuthorEditWidget::currentAuthorList() const
{
    QStringList ret;

    for(int i = 0; i < authorList->count(); i++) {
        ret += authorList->item(i)->text();
    }

    return ret;
}

void AuthorEditWidget::addAuthor()
{
    QString authorName = authorComboBox->currentText();

    if(!authorName.isNull() && !authorName.isEmpty()) {
        addAuthor(authorName);
    }
}

void AuthorEditWidget::addAuthor(const QString& name)
{
    QString normName = normalizeName(name);

    if(!authorExists(normName)) {

        authorList->addItem(normName);
        authorComboBox->setEditText(QString());
    }
}

void AuthorEditWidget::removeSelectedAuthor()
{
    if(authorList->currentItem() != 0) {

        authorList->takeItem(authorList->row(authorList->currentItem()));
    }
}

void AuthorEditWidget::setCurrentAuthor(const QString& fullName)
{
    authorComboBox->setEditText(fullName);
}

void AuthorEditWidget::acquireAuthor()
{
    QString author = PDFDocumentDialog::selectString(mLocalUrl);

    setCurrentAuthor(author.simplified());
}

bool AuthorEditWidget::authorExists(const QString& name)
{
    return currentAuthorList().contains(name);
}

QString AuthorEditWidget::normalizeName(const QString& name) const
{
    QStringList partsComma = name.split(',');
    QStringList partsSpace = name.split(' ');

    QString firstName, lastName;

    if(partsComma.count() == 2) {
        firstName = partsComma[1].trimmed();
        lastName = partsComma[0].trimmed();

    } else if(partsSpace.count() == 2) {
        firstName = partsSpace[0].trimmed();
        lastName = partsSpace[1].trimmed();
    }

    return lastName + ", " + firstName;
}
