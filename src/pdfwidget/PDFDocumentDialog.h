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

#ifndef PDFDOCUMENTDIALOG_H_
#define PDFDOCUMENTDIALOG_H_

#include <QDialog>
#include <QString>

class QPushButton;
class PDFDocumentWidget;

class PDFDocumentDialog : public QDialog
{
    public:
        PDFDocumentDialog();
        virtual ~PDFDocumentDialog();

        static QString selectString(const QString& fileName);

    private:
        PDFDocumentWidget *mDocWidget;
        QPushButton *mOKButton;
};

#include <QObject>

class SignalCatcher : public QObject
{
    Q_OBJECT

    public:
        SignalCatcher();
        ~SignalCatcher();

        QString catchedString() const
        {
            return mCatchedString;
        }

    public Q_SLOTS:
        void catchString(const QString& str);

    private:
        QString mCatchedString;
};


#endif /* PDFDOCUMENTDIALOG_H_ */
