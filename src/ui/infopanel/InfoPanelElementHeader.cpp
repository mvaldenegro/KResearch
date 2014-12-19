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

#include "InfoPanelElementHeader.h"

#include <QFontMetrics>
#include <QPainter>

InfoPanelElementHeader::InfoPanelElementHeader(QWidget *parent)
: QWidget(parent)
{
}

InfoPanelElementHeader::~InfoPanelElementHeader()
{
}

void InfoPanelElementHeader::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int lineY = height() - 2;

    QPainter p(this);
    p.setPen(Qt::darkGray);
    p.drawLine(0, lineY, size().width(), lineY);

    p.setPen(Qt::black);
    p.drawText(rect(), Qt::AlignLeft, mTitle);
}

void InfoPanelElementHeader::updateMinimumSize()
{
    QFontMetrics fm = QFontMetrics(font());
    int w = fm.width(title());
    int h = fm.height();

    setMinimumSize(w, h + 5);
}
