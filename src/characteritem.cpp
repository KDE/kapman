/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "characteritem.h"

CharacterItem::CharacterItem(Character *p_model) : ElementItem(p_model)
{
    connect(p_model, &Character::eaten, this, &CharacterItem::startBlinking);
}

CharacterItem::~CharacterItem()
{
    delete m_blinkTimer;
}

QPainterPath CharacterItem::shape() const
{
    QPainterPath path;
    // Temporary variable to keep the boundingRect available
    QRectF rect = boundingRect();

    // Calculation of the shape
    QRectF shapeRect = QRectF(rect.x() + rect.width() / 4, rect.y() + rect.height() / 4, rect.width() / 2, rect.height() / 2);
    path.addEllipse(shapeRect);
    return path;
}

void CharacterItem::update(qreal p_x, qreal p_y)
{
    // Compute the top-right coordinates of the item
    qreal x = p_x - boundingRect().width() / 2;
    qreal y = p_y - boundingRect().height() / 2;
    // Updates the view coordinates
    setPos(x, y);
}

void CharacterItem::startBlinking()
{
    m_nbBlinks = 0;
    m_blinkTimer->start();
}

void CharacterItem::blink()
{
    m_nbBlinks++;
}

