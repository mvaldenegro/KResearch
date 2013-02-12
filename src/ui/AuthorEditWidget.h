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

#ifndef AUTHOREDITWIDGET_H_
#define AUTHOREDITWIDGET_H_

#include <library/Author.h>

#include <QWidget>

#include "ui_AuthorEdit.h"

class AuthorEditWidget : public QWidget, public Ui::AuthorEdit
{
    Q_OBJECT

    public:
        AuthorEditWidget(QWidget *parent = 0);
        virtual ~AuthorEditWidget();

        void setAuthorList(const QStringList& authors);
        void setLocalUrl(const QString& localUrl);

        QStringList currentAuthorList() const;

    public Q_SLOTS:
        void addAuthor();
        void removeSelectedAuthor();
        void acquireAuthor();

    protected Q_SLOTS:
        void addAuthor(const QString& name);
        void setCurrentAuthor(const QString& fullName);

    protected:
        bool authorExists(const QString& fullName);
        QString normalizeName(const QString& name) const;

    private:
        QString mLocalUrl;
};

#endif /* AUTHOREDITWIDGET_H_ */
