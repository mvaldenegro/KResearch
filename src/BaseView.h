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

#ifndef BASEVIEW_H_
#define BASEVIEW_H_

#include <QWidget>

class DocumentImportService;
class QTableView;

class BaseView : public QWidget
{
    Q_OBJECT

    public:
        BaseView(QWidget *parent = 0);
        virtual ~BaseView();

        DocumentImportService *importService() const
        {
            return mImportService;
        }

        virtual void saveConfig();
        virtual void loadConfig();

    protected:
        void configureTableView(QTableView *view);

    private:
        DocumentImportService *mImportService;
};

#endif /* BASEVIEW_H_ */
