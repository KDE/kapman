/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
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


#include "kapman.h"

#include <KGameDifficulty>

Kapman::Kapman(qreal p_x, qreal p_y, Maze* p_maze) : Character(p_x, p_y, p_maze) {
	m_type = Element::KAPMAN;
}

Kapman::~Kapman() {

}

void Kapman::init() {
	goRight();
	updateDirection();
	// Stop animation
	emit(stopped());
}

void Kapman::goUp() {
	m_askedXSpeed = 0;
	m_askedYSpeed = -m_speed;
}

void Kapman::goDown() {
	m_askedXSpeed = 0;
	m_askedYSpeed = m_speed;
}

void Kapman::goRight() {
	m_askedXSpeed = m_speed;
	m_askedYSpeed = 0;
}

void Kapman::goLeft() {
	m_askedXSpeed = -m_speed;
	m_askedYSpeed = 0;
}

void Kapman::updateDirection() {
	setXSpeed(m_askedXSpeed);
	setYSpeed(m_askedYSpeed);
	m_askedXSpeed = 0;
	m_askedYSpeed = 0;
	// Signal to the kapman item that the direction changed
	emit(directionChanged());
}

void Kapman::updateMove() {
	// If the kapman does not move
	if (m_xSpeed == 0 && m_ySpeed == 0) {
		// If the user asks for moving
		if (m_askedXSpeed != 0 || m_askedYSpeed != 0) {
			// Check the next cell with the asked direction
			if (getAskedNextCell().getType() == Cell::CORRIDOR) {
				// Update the direction
				updateDirection();
				// Move the kapman
				move();
			}
		}
	}
	// If the kapman is already moving
	else {
		// If the kapman wants to go back it does not wait to be on a center
		if ( (m_xSpeed!=0 && m_askedXSpeed==-m_xSpeed) || (m_ySpeed!=0 && m_askedYSpeed==-m_ySpeed) ) {
			// Go back
			updateDirection();
			// Move the kapman
			move();
		} else {
			// If the kapman gets on a cell center
			if (onCenter()) {
				// If there is an asked direction (but not a half-turn)
				if ((m_askedXSpeed != 0 || m_askedYSpeed != 0) && (m_askedXSpeed != m_xSpeed || m_askedYSpeed != m_ySpeed)) {
					// Check the next cell with the kapman asked direction
					if (getAskedNextCell().getType() == Cell::CORRIDOR) {
						// Move the kapman on the cell center
						moveOnCenter();
						// Update the direction
						updateDirection();
					} else {
						// Check the next cell with the kapman current direction
						if (getNextCell().getType() != Cell::CORRIDOR) {
							// Move the kapman on the cell center
							moveOnCenter();
							// Stop moving
							stopMoving();
						} else {
							// Move the kapman
							move();
						}
					}
				} else {
					// Check the next cell with the kapman current direction
					if (getNextCell().getType() != Cell::CORRIDOR) {
						// Move the kapman on the cell center
						moveOnCenter();
						// Stop moving
						stopMoving();
					} else {
						// Move the kapman
						move();
					}
				}
			} else {
				// Move the kapman
				move();
			}
		}
	}
}

void Kapman::winPoints(Element* p_element) {
	// Emits a signal to the game
	emit(sWinPoints(p_element));
}

void Kapman::die() {
	emit(eaten());
}

void Kapman::emitGameUpdated() {
	emit(gameUpdated());
}

qreal Kapman::getAskedXSpeed() const {
	return m_askedXSpeed;
}

qreal Kapman::getAskedYSpeed() const {
	return m_askedYSpeed;
}

Cell Kapman::getAskedNextCell() {
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(m_y);
	int curCellCol = m_maze->getColFromX(m_x);
	Cell nextCell;

	// Get the next cell function of the character asked direction
	if (m_askedXSpeed > 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
	} else if (m_askedXSpeed < 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
	} else if (m_askedYSpeed > 0) {
		nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
	} else if (m_askedYSpeed < 0) {
		nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
	}

	return nextCell;
}

void Kapman::stopMoving() {
	setXSpeed(0);
	setYSpeed(0);
	m_askedXSpeed = 0;
	m_askedYSpeed = 0;
	emit(stopped());
}

void Kapman::initSpeedInc() {
	// Kapman speed increase when level up
	if(KGameDifficulty::level() == KGameDifficulty::Easy) {
	//s_speed == LOW_SPEED) {
		m_speedIncrease = (Character::LOW_SPEED_INC / 2);
	}
	if(KGameDifficulty::level() == KGameDifficulty::Medium) {
		m_speedIncrease = (Character::MEDIUM_SPEED_INC / 2);
	}
	if(KGameDifficulty::level() == KGameDifficulty::Hard) {
		m_speedIncrease = (Character::HIGH_SPEED_INC / 2);
	}
}
