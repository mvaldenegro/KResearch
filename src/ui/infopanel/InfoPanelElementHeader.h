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
 * along with KResearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INFOPANELELEMENTHEADER_H_
#define INFOPANELELEMENTHEADER_H_

#include <QWidget>

class InfoPanelElementHeader : public QWidget
{
    Q_OBJECT

    public:
        InfoPanelElementHeader(QWidget *parent = nullptr);
        virtual ~InfoPanelElementHeader();

        QString title() const
        {
            return mTitle;
        }

        void setTitle(const QString& title)
        {
            mTitle = title;
            updateMinimumSize();
        }

        QFont titleFont() const
        {
            return mTitleFont;
        }

        void setTitleFont(const QFont& titleFont)
        {
            mTitleFont = titleFont;
            updateMinimumSize();
        }

    protected:
        void paintEvent(QPaintEvent *event);
        void updateMinimumSize();

    private:
        QString mTitle;
        QFont mTitleFont;
};
#endif /* INFOPANELELEMENTHEADER_H_ */
