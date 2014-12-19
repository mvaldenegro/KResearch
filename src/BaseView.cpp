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

#include "BaseView.h"

#include <QTableView>
#include <QHeaderView>

#include <library/Repository.h>

BaseView::BaseView(QWidget *parent)
 : QWidget(parent)
{
}

BaseView::~BaseView()
{
}

void BaseView::saveConfig()
{
}

void BaseView::loadConfig()
{
}

void BaseView::configureTableView(QTableView *view)
{
    view->setAlternatingRowColors(true);
    view->verticalHeader()->hide();
    view->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);

    view->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    view->setShowGrid(false);
}
