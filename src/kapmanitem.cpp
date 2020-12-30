/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Nathalie Liesse <nathalie.liesse@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kapmanitem.h"
#include "ghost.h"
#include "settings.h"

#include <QGraphicsScene>
#include <KgDifficulty>

const int KapmanItem::NB_FRAMES = 32;
const int KapmanItem::ANIM_LOW_SPEED = 500;
const int KapmanItem::ANIM_MEDIUM_SPEED = 400;
const int KapmanItem::ANIM_HIGH_SPEED = 300;

KapmanItem::KapmanItem(Kapman *p_model) : CharacterItem(p_model)
{
    connect(p_model, &Kapman::directionChanged, this, &KapmanItem::updateDirection);
    connect(p_model, &Kapman::gameUpdated, this, &KapmanItem::manageCollision);
    connect(p_model, &Kapman::stopped, this, &KapmanItem::stopAnim);

    // A timeLine for the Kapman animation
    m_animationTimer = new QTimeLine();
    m_animationTimer->setEasingCurve(QEasingCurve::SineCurve);
    m_animationTimer->setLoopCount(0);
    m_animationTimer->setFrameRange(0, NB_FRAMES - 1);
    // Animation speed
    switch ((int) Kg::difficultyLevel()) {
    case KgDifficultyLevel::Easy:
        m_animationTimer->setDuration(KapmanItem::ANIM_LOW_SPEED);
        break;
    case KgDifficultyLevel::Medium:
        m_animationTimer->setDuration(KapmanItem::ANIM_MEDIUM_SPEED);
        break;
    case KgDifficultyLevel::Hard:
        m_animationTimer->setDuration(KapmanItem::ANIM_HIGH_SPEED);
        break;
    }
    connect(m_animationTimer, &QTimeLine::frameChanged, this, &KapmanItem::setFrame);

    // Define the timer which sets the blinking frequency
    m_blinkTimer = new QTimer(this);
    m_blinkTimer->setInterval(400);
    connect(m_blinkTimer, &QTimer::timeout, this, &KapmanItem::blink);
}

KapmanItem::~KapmanItem()
{
    delete m_animationTimer;
}

void KapmanItem::updateDirection()
{
    QTransform transform;
    int angle = 0;
    Kapman *model = (Kapman *)getModel();

    // Compute the angle
    if (model->getXSpeed() > 0) {
        angle = 0;
    } else if (model->getXSpeed() < 0) {
        angle = 180;    // The default image is right oriented
    }
    if (model->getYSpeed() > 0) {
        angle = 90;
    } else if (model->getYSpeed() < 0) {
        angle = -90;
    }

    if (m_rotationFlag == 0) {
        angle = 0;
    }
    // Rotate the item
    transform.translate(boundingRect().width() / 2, boundingRect().height() / 2);
    transform.rotate(angle);
    transform.translate(-boundingRect().width() / 2, -boundingRect().height() / 2);
    setTransform(transform);
}

void KapmanItem::manageCollision()
{
    QList<QGraphicsItem *> collidingList = collidingItems();

    // The signal is emitted only if the list contains more than 1 items (to exclude the case
    // when the kapman only collides with the maze)
    if (collidingList.size() > 1) {
        for (int i = 0; i < collidingList.size(); ++i) {
            // The maze and the points labels have a negative zValue which allows to exclude them from the treatment of collisions
            if (collidingList[i]->zValue() >= 0) {
                ElementItem *item = dynamic_cast<ElementItem *>(collidingList[i]);
                if (item) {
                    item->getModel()->doActionOnCollision((Kapman *)getModel());
                }
            }
        }
    }
}

void KapmanItem::update(qreal p_x, qreal p_y)
{
    ElementItem::update(p_x, p_y);

    // If the kapman is moving
    if (((Kapman *)getModel())->getXSpeed() != 0 || ((Kapman *)getModel())->getYSpeed() != 0) {
        startAnim();
    }
}

void KapmanItem::startAnim()
{
    // Start the animation timer if it is not active
    if (m_animationTimer->state() != QTimeLine::Running) {
        m_animationTimer->start();
    }
}

void KapmanItem::pauseAnim()
{
    if (m_animationTimer->state() == QTimeLine::Running) {
        m_animationTimer->setPaused(true);
    }
}

void KapmanItem::resumeAnim()
{
    if (m_animationTimer->state() == QTimeLine::Running) {
        m_animationTimer->setPaused(false);
    }
}

void KapmanItem::stopAnim()
{
    setElementId(QStringLiteral("kapman_0"));
    if (m_animationTimer->state() == QTimeLine::Running) {
        m_animationTimer->stop();
    }
}

void KapmanItem::setFrame(const int p_frame)
{
    setElementId(QStringLiteral("kapman_%1").arg(p_frame));
}

void KapmanItem::startBlinking()
{
    stopAnim();
    setElementId(QStringLiteral("kapman_0"));
    CharacterItem::startBlinking();
}

void KapmanItem::blink()
{
    CharacterItem::blink();
    if (m_nbBlinks % 2 == 0) {
        setElementId(QStringLiteral("kapman_0"));
    } else {
        setElementId(QStringLiteral("kapman_blink"));
    }
    // Make the kapman blink 2 times (4 ticks)
    if (m_nbBlinks == 4) {
        m_blinkTimer->stop();
    }
}

