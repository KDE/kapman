/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "element.h"

Element::Element(qreal p_x, qreal p_y, Maze *p_maze) : m_xInit(p_x), m_yInit(p_y),  m_maze(p_maze)
{
    m_points = 0;
    initCoordinate();
}

Element::~Element()
{
}

void Element::doActionOnCollision(Kapman *)
{
    // Do nothing by default : will be redefined within the subclasses
}

qreal Element::getX() const
{
    return m_x;
}

qreal Element::getY() const
{
    return m_y;
}

void Element::setX(qreal p_x)
{
    m_x = p_x;
    Q_EMIT moved(m_x, m_y);
}

void Element::setY(qreal p_y)
{
    m_y = p_y;
    Q_EMIT moved(m_x, m_y);
}

int Element::getPoints() const
{
    return m_points;
}

Element::Type Element::getType() const
{
    return m_type;
}

QString Element::getImageId() const
{
    return m_imageId;
}

void  Element::setImageId(const QString &p_imageId)
{
    m_imageId = p_imageId;
}

void Element::initCoordinate()
{
    setX(m_xInit);
    setY(m_yInit);
}
