/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoit Besse <besse.pb@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ghostitem.h"
#include "game.h"

GhostItem::GhostItem(Ghost *p_model) : CharacterItem(p_model)
{
    connect(p_model, &Ghost::stateChanged, this, &GhostItem::updateState);

    // Calculations for the duration of blinking stuff
    const int blinkTimerDuration = (int)(500 * Game::s_durationRatio);
    // Define the timer which sets the blinking frequency
    m_blinkTimer = new QTimer(this);
    m_blinkTimer->setInterval(blinkTimerDuration);
    connect(m_blinkTimer, &QTimer::timeout, this, &GhostItem::blink);
}

GhostItem::~GhostItem()
{
    delete m_blinkTimer;
}

void GhostItem::update(qreal p_x, qreal p_y)
{
    // Compute the top-right coordinates of the item
    qreal x = p_x - boundingRect().width() / 2;
    qreal y = p_y - boundingRect().height() / 2;
    // Updates the view coordinates
    setPos(x, y);
}

void GhostItem::updateState()
{
    if (m_blinkTimer->isActive()) {
        m_blinkTimer->stop();
    }
    switch (((Ghost *)getModel())->getState()) {
    case Ghost::PREY:
        m_blinkTimer->start();
        setElementId(QStringLiteral("scaredghost"));
        // The ghosts are now weaker than the kapman, so they are under him
        setZValue(1);
        break;
    case Ghost::HUNTER:
        setElementId(((Ghost *)getModel())->getImageId());
        // The ghosts are stronger than the kapman, they are above him
        setZValue(3);
        break;
    case Ghost::EATEN:
        setElementId(QStringLiteral("ghosteye"));
        // The ghosts are now weaker than the kapman, so they are under him
        setZValue(1);
        break;
    }
}

void GhostItem::blink()
{
    if (((Ghost *)getModel())->getState() == Ghost::PREY
            && ((Ghost *)getModel())->preyStateAlmostOver()) {
        CharacterItem::blink();
        if (m_nbBlinks % 2 == 0) {
            setElementId(QStringLiteral("scaredghost"));
        } else {
            setElementId(QStringLiteral("whitescaredghost"));
        }
    }
}
