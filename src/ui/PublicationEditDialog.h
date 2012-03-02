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

#ifndef PUBLICATIONEDITDIALOG_H_
#define PUBLICATIONEDITDIALOG_H_

#include "ui_PublicationEdit.h"

#include <library/Publication.h>

#include <QDialog>

class Repository;
class AuthorEditWidget;

class PublicationEditDialog : public QDialog, public Ui_PublicationEditor
{
    Q_OBJECT

    public:
        PublicationEditDialog(Publication::Ptr pubToEdit);
        virtual ~PublicationEditDialog();

        static Publication::Ptr editPublication(Publication::Ptr pub);

    protected Q_SLOTS:
        void selectLocalURL();
        void save();

        void acquireTitle();
        void acquireAbstract();
        void acquireYear();
        void acquireJournal();
        void acquireConference();
        void acquirePublisher();
        void acquireSeries();
        void acquireSubseries();
        void acquireUrl();
        void acquireDoi();
        void acquireIsbn();


    protected:
        void fill(Publication::Ptr pub);
        void setupAutocompletions();
        void saveAuthors();

    private:
        AuthorEditWidget *mEditWidget;

        Publication::Ptr mPub;
};

#endif /* PUBLICATIONEDITDIALOG_H_ */
