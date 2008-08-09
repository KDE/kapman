/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Pierre-Benoit Besse <besse.pb@gmail.com>
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

#include "ghostitem.h"

GhostItem::GhostItem(Ghost* p_model, const QString & p_imagePath) : CharacterItem (p_model, p_imagePath) {
	connect(p_model, SIGNAL(stateChanged()), this, SLOT(updateState()));
	m_startBlinkingTimer = new QTimer(this);
	m_startBlinkingTimer->setInterval(7500);
	m_startBlinkingTimer->setSingleShot(true);
	connect(m_startBlinkingTimer, SIGNAL(timeout()), this, SLOT(startBlinking()));
}

GhostItem::~GhostItem() {
	delete m_startBlinkingTimer;
}

void GhostItem::update(qreal p_x, qreal p_y) {
	// Compute the top-right coordinates of the item
	qreal x = p_x - boundingRect().width() / 2;
	qreal y = p_y - boundingRect().height() / 2;
	// Updates the view coordinates
	setPos(x, y);
}

void GhostItem::updateState() {
	// Stop timers
	if (m_startBlinkingTimer->isActive()) {
		m_startBlinkingTimer->stop();
	}
	if (m_blinkTimer->isActive()) {
		m_blinkTimer->stop();
	}
	switch (((Ghost*)getModel())->getState()) { 
		case Ghost::PREY:
			setElementId("ghost_prey");
			m_startBlinkingTimer->start();
			break;
		case Ghost::HUNTER:
			setElementId("ghost_hunter");
			break;
		case Ghost::EATEN:
			setElementId("ghost_eaten");
			break;
	}
}

void GhostItem::blink() {
	CharacterItem::blink();
	if (m_nbBlinks % 2 == 0) {
		setElementId("ghost_prey");
	} else {
		setElementId("ghost_prey_white");
	}
}

