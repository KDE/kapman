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
#include "game.h"

GhostItem::GhostItem(Ghost* p_model) : CharacterItem (p_model) {
	connect(p_model, SIGNAL(stateChanged()), this, SLOT(updateState()));

	// Calculations for the duration of blinking stuff
	int blinkTimerDuration = (int)(500 * Game::s_durationRatio);
	int startBlinkingTimerDuration = (int)(Game::s_preyStateDuration*Game::s_durationRatio - 5*blinkTimerDuration);

	// Define the timer which tells the ghosts to start blinking when about to leave prey state
	m_startBlinkingTimer = new QTimer(this);
	m_startBlinkingTimer->setInterval(startBlinkingTimerDuration);
	m_startBlinkingTimer->setSingleShot(true);
	connect(m_startBlinkingTimer, SIGNAL(timeout()), this, SLOT(startBlinking()));

	// Define the timer which sets the blinking frequency
	m_blinkTimer = new QTimer(this);
	m_blinkTimer->setInterval(blinkTimerDuration);
	connect(m_blinkTimer, SIGNAL(timeout()), this, SLOT(blink()));
}

GhostItem::~GhostItem() {
	delete m_startBlinkingTimer;
}

void GhostItem::updateBlinkTimersDuration() {
	// Set the timers duration depending on the prey state duration
	int blinkTimerDuration = (int)( (Game::s_preyStateDuration*Game::s_durationRatio) / 20);
	int startBlinkingTimerDuration = (int)(blinkTimerDuration * 15);
	m_blinkTimer->setInterval(blinkTimerDuration);
	m_startBlinkingTimer->setInterval(startBlinkingTimerDuration);
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
			updateBlinkTimersDuration();
			setElementId("scaredghost");
			m_startBlinkingTimer->start();
			// The ghosts are now weaker than the kapman, so they are under him
			setZValue(1);
			break;
		case Ghost::HUNTER:
			setElementId( ((Ghost*)getModel())->getImageId() );
			// The ghosts are stronger than the kapman, they are above him
			setZValue(3);
			break;
		case Ghost::EATEN:
			setElementId("ghosteye");
			// The ghosts are now weaker than the kapman, so they are under him
			setZValue(1);
			break;
	}
}

void GhostItem::blink() {
	CharacterItem::blink();
	if (m_nbBlinks % 2 == 0) {
		setElementId("scaredghost");
	} else {
		setElementId("whitescaredghost");
	}
}

