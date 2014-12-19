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
 * along with Epic Framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "JournalView.h"

#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>

#include <library/Repository.h>
#include <library/model/JournalModel.h>

JournalView::JournalView(QWidget *parent)
 : BaseView(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    mJournalView = new QTableView(this);
    mJournalView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    configureTableView(mJournalView);

    mJournalView->setModel(new JournalModel(Repository::self()->publicationDAO()));

    layout->addWidget(mJournalView);
}

JournalView::~JournalView()
{
}

