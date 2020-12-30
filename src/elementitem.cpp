/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "elementitem.h"

ElementItem::ElementItem(Element *p_model) : QGraphicsSvgItem()
{
    m_model = p_model;
    // Init the view coordinates
    setPos(p_model->getX() - boundingRect().width() / 2, p_model->getY() - boundingRect().height() / 2);
    // Connects the model to the view
    connect(p_model, &Element::moved, this, &ElementItem::update);
    setCacheMode(DeviceCoordinateCache);
    setMaximumCacheSize(QSize(500, 500));
}

ElementItem::~ElementItem()
{
    delete m_model;

}

Element *ElementItem::getModel() const
{
    return m_model;
}

QPainterPath ElementItem::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void ElementItem::update(qreal p_x, qreal p_y)
{
    // Compute the top-right coordinates of the item
    qreal x = p_x - boundingRect().width() / 2;
    qreal y = p_y - boundingRect().height() / 2;

    // Updates the view coordinates
    setPos(x, y);
}
