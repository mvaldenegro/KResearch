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

#ifndef CENTRALVIEW_H_
#define CENTRALVIEW_H_

#include <QWidget>

#include <library/Publication.h>

class QModelIndex;
class QToolBar;
class QTableView;
class KLineEdit;

class Repository;
class PublicationImportService;

class LibraryView : public QWidget
{
    Q_OBJECT

    public:
        LibraryView(QWidget *parent = 0);
        virtual ~LibraryView();

        Publication::Ptr selectedPublication() const
        {
            return mSelectedPub;
        }

    public Q_SLOTS:
        void import();
        void edit();

    signals:
        void activated(const QString& fileName);
        void selected(Publication::Ptr pub);

    protected Q_SLOTS:
        void activated(const QModelIndex& idx);
        void clicked(const QModelIndex &idx);

    private:
        void setupToolbar();

        QToolBar *mToolBar;
        QTableView *mArticleView;
        KLineEdit *mSearchEdit;

        Publication::Ptr mSelectedPub;

        Repository *mRepository;
        PublicationImportService *mImportService;
};

#endif /* CENTRALVIEW_H_ */
