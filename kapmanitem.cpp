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

KapmanItem::KapmanItem(Kapman* p_model, const QString & p_imagePath) : CharacterItem(p_model, p_imagePath) {
	connect(p_model, SIGNAL(directionChanged()), this, SLOT(updateDirection()));
	connect(p_model, SIGNAL(gameUpdated()), this, SLOT(manageCollision()));
	
	m_animationTimer = new QTimeLine();
	m_animationTimer->setDuration(500);
	m_animationTimer->setCurveShape(QTimeLine::SineCurve);
	m_animationTimer->setLoopCount(0);
	m_animationTimer->setUpdateInterval(15);
	m_animationTimer->start();
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
	QList<QGraphicsItem *> collidingList = collidingItems();

	// The signal is emitted only if the list contains more than 1 items (to exclude the case
	// when the kapman only collides with the maze)
	if(collidingList.size() > 1) {
		for(int i = 0 ; i < collidingList.size() ; i++) {
			// The maze has a negative zValue which allows to exclude it from the treatment of collisions
			if (collidingList[i]->zValue() >= 0) {
				((ElementItem*)collidingList[i])->getModel()->doActionOnCollision((Kapman*)getModel());
			}
		}
	}
}

void KapmanItem::update(qreal p_x, qreal p_y) {
	// Compute the top-right coordinates of the item
	qreal x = p_x - boundingRect().width() / 2;
	qreal y = p_y - boundingRect().height() / 2;
	
	qreal current = m_animationTimer->currentValue();
	int currentFrame = (int)(current * (NB_FRAMES - 1));
	
	setElementId(QString("kapman_") += QString::number(currentFrame));
	
	// Updates the view coordinates
	setPos(x, y);
}

void KapmanItem::startBlinking() {
	setElementId(QString("kapman_") += QString::number(NB_FRAMES - 1));
	CharacterItem::startBlinking();
}

void KapmanItem::blink() {
	CharacterItem::blink();
	if (m_nbBlinks % 2 == 0) {
		setElementId(QString("kapman_") += QString::number(NB_FRAMES - 1));
	} else {
		setElementId("kapman_blink");
	}
	// Make the kapman blink 2 times (4 ticks)
	if (m_nbBlinks == 4) {
		m_blinkTimer->stop();
	}
}

