/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Nathalie Liesse <nathalie.liesse@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "kapmanitem.h"
#include "characteritem.h"
#include "ghost.h"

#include <QGraphicsScene>

const int KapmanItem::NB_FRAMES = 32;
const int KapmanItem::ANIM_LOW_SPEED = 500;
const int KapmanItem::ANIM_MEDIUM_SPEED = 400;
const int KapmanItem::ANIM_HIGH_SPEED = 300;

KapmanItem::KapmanItem(Kapman* p_model, const QString & p_imagePath) : CharacterItem(p_model, p_imagePath) {
	connect(p_model, SIGNAL(directionChanged()), this, SLOT(updateDirection()));
	connect(p_model, SIGNAL(gameUpdated()), this, SLOT(manageCollision()));
	connect(p_model, SIGNAL(stopped()), this, SLOT(stopAnim()));
	
	m_animationTimer = new QTimeLine();
	m_animationTimer->setCurveShape(QTimeLine::SineCurve);
	m_animationTimer->setLoopCount(0);
	m_animationTimer->setFrameRange(0, NB_FRAMES - 1);
	// Animation speed
	if (Character::getCharactersSpeed() == Character::LOW_SPEED) {
		m_animationTimer->setDuration(KapmanItem::ANIM_LOW_SPEED);
	} else if (Character::getCharactersSpeed() == Character::MEDIUM_SPEED) {
		m_animationTimer->setDuration(KapmanItem::ANIM_MEDIUM_SPEED);
	} else if (Character::getCharactersSpeed() == Character::HIGH_SPEED) {
		m_animationTimer->setDuration(KapmanItem::ANIM_HIGH_SPEED);
	}
	connect(m_animationTimer, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
	setElementId("kapman_0");
}

KapmanItem::~KapmanItem() {
	delete m_animationTimer;
}

void KapmanItem::updateDirection() {
	QTransform transform;
	int angle = 0;
	Kapman* model = (Kapman*)getModel();

	// Compute the angle
	if (model->getXSpeed() > 0) {
		angle = 0;
	} else if (model->getXSpeed() < 0) {
		angle = 180;	// The default image is right oriented
	}
	if (model->getYSpeed() > 0) {
		angle = 90;
	} else if (model->getYSpeed() < 0) {
		angle = -90;
	}
	// Rotate the item
	transform.translate(boundingRect().width() / 2, boundingRect().height() / 2);
	transform.rotate(angle);
	transform.translate(-boundingRect().width() / 2, -boundingRect().height() / 2);
	setTransform(transform);
}

void KapmanItem::manageCollision() {
	QList<QGraphicsItem*> collidingList = collidingItems();

	// The signal is emitted only if the list contains more than 1 items (to exclude the case
	// when the kapman only collides with the maze)
	if (collidingList.size() > 1) {
		for (int i = 0; i < collidingList.size(); i++) {
			// The maze has a negative zValue which allows to exclude it from the treatment of collisions
			if (collidingList[i]->zValue() >= 0) {
				((ElementItem*)collidingList[i])->getModel()->doActionOnCollision((Kapman*)getModel());
			}
		}
	}
}

void KapmanItem::update(qreal p_x, qreal p_y) {
	ElementItem::update(p_x, p_y);
	
	// If the kapman is moving
	if (((Kapman*)getModel())->getXSpeed() != 0 || ((Kapman*)getModel())->getYSpeed() != 0) {
		startAnim();
	}
}

void KapmanItem::startAnim() {
	// Start the animation timer if it is not active
	if (m_animationTimer->state() != QTimeLine::Running) {
		m_animationTimer->start();
	}
}

void KapmanItem::pauseAnim() {
        if (m_animationTimer->state() == QTimeLine::Running)
	    m_animationTimer->setPaused(true);
}

void KapmanItem::resumeAnim() {
        if (m_animationTimer->state() == QTimeLine::Running)
	    m_animationTimer->setPaused(false);
}

void KapmanItem::stopAnim() {
	setElementId("kapman_0");
        if (m_animationTimer->state() == QTimeLine::Running)
	    m_animationTimer->stop();
}

void KapmanItem::setFrame(const int p_frame) {
	setElementId(QString("kapman_") += QString::number(p_frame));
}

void KapmanItem::startBlinking() {
	stopAnim();
	setElementId("kapman_0");
	CharacterItem::startBlinking();
}

void KapmanItem::blink() {
	CharacterItem::blink();
	if (m_nbBlinks % 2 == 0) {
		setElementId("kapman_0");
	} else {
		setElementId("kapman_blink");
	}
	// Make the kapman blink 2 times (4 ticks)
	if (m_nbBlinks == 4) {
		m_blinkTimer->stop();
	}
}

