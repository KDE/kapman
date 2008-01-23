/* This file is part of Kapman.
   Created by Pierre-Benoit Besse <besse.pb@gmail.com>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
*/

#include "character.h"

const qreal Character::SPEED = 2.0;

Character::Character(qreal p_x, qreal p_y, Maze* p_maze) :
		m_x(p_x), m_y(p_y), m_xSpeed(0), m_ySpeed(0), m_maze(p_maze) {

}

Character::~Character() {

}

void Character::move() {
	if(m_maze->getColFromX(m_x + m_xSpeed) == 0) {
		m_x = (m_maze->getNbColumns()-1.5) * Cell::SIZE;
	}
	else if(m_maze->getColFromX(m_x + m_xSpeed) == m_maze->getNbColumns()-1) {
		m_x = 1.5 * Cell::SIZE;
	}
	else if(m_maze->getRowFromY(m_y + m_ySpeed) == 0) {
		m_y = (m_maze->getNbRows()-1.5) * Cell::SIZE;
	}
	else if(m_maze->getRowFromY(m_y + m_ySpeed) == m_maze->getNbRows()-1) {
		m_y = 1.5 * Cell::SIZE;
	}
	
	m_x += m_xSpeed;
	m_y += m_ySpeed;
	
	emit(moved(m_x, m_y));
}

/** Accessors */
qreal Character::getX() const {
	return m_x;
}

qreal Character::getY() const {
	return m_y;
}

qreal Character::getXSpeed() const {
	return m_xSpeed;
}

qreal Character::getYSpeed() const {
	return m_ySpeed;
}

void Character::setX(qreal p_x) {
	m_x = p_x;
	emit(moved(m_x, m_y));
}

void Character::setY(qreal p_y) {
	m_y = p_y;
	emit(moved(m_x, m_y));
}

void Character::setXSpeed(qreal p_xSpeed) {
	m_xSpeed = p_xSpeed;
}

void Character::setYSpeed(qreal p_ySpeed) {
	m_ySpeed = p_ySpeed;
}

bool Character::isInLineSight(Character * p_c) {
	int curCallerRow, curCallerCol, curCharacterRow, curCharacterCol;
	
	//init
	curCallerRow = m_maze->getRowFromY(m_y);
	curCallerCol = m_maze->getColFromX(m_x);
	curCharacterRow = m_maze->getRowFromY(p_c->getY());
	curCharacterCol = m_maze->getColFromX(p_c->getX());
	
	//Same row
	if(curCallerRow == curCharacterRow ) {
		if(curCallerCol > curCharacterCol && m_xSpeed < 0) {
			//foreach column, test if it's a wall or not between the two cells
			for(int i=curCharacterCol; i<curCallerCol; i++) {
				if(m_maze->getCell(curCallerRow, i).getType() != Cell::CORRIDOR) {
					return false;
				}
			}
			return true;
		}
		else if(curCallerCol < curCharacterCol && m_xSpeed > 0) {
			for(int i=curCallerCol; i<curCharacterCol; i++) {
				if(m_maze->getCell(curCallerRow, i).getType() != Cell::CORRIDOR) {
					return false;
				}
			}
			return true;
		}
	}
	//Same column
	else if (curCallerCol == curCharacterCol) {
		if(curCallerRow > curCharacterRow && m_ySpeed < 0) {
			//foreach row, test if it's a wall or not between the two cells
			for(int i=curCharacterRow; i<curCallerRow; i++) {
				if(m_maze->getCell(i, curCallerCol).getType() != Cell::CORRIDOR) {
					return false;
				}
			}
			return true;
		}
		else if(curCallerRow < curCharacterRow && m_ySpeed > 0) {
			for(int i=curCallerRow; i<curCharacterRow; i++) {
				if(m_maze->getCell(i, curCallerCol).getType() != Cell::CORRIDOR) {
					return false;
				}
			}
			return true;
		}
	}
	return false;
	
}

/** Private */
Cell Character::getNextCell() {
	Cell nextCell;
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(m_y);
	int curCellCol = m_maze->getColFromX(m_x);

	// Get the next cell function of the character direction
	if (m_xSpeed > 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
	}
	else if (m_xSpeed < 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
	}
	else if (m_ySpeed > 0) {
		nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
	}
	else if (m_ySpeed < 0) {
		nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
	}

	return nextCell;
}

bool Character::onCenter() {
	// Get the current cell center coordinates
	qreal centerX = (m_maze->getColFromX(m_x) + 0.5) * Cell::SIZE;
	qreal centerY = (m_maze->getRowFromY(m_y) + 0.5) * Cell::SIZE;
	bool willGoPast = false;

	// Will the character go past the center of the cell it's on ?
	// If goes right
	if (m_xSpeed > 0) {
		willGoPast = (m_x <= centerX && m_x + m_xSpeed >= centerX);
	}
	// If goes left
	else if (m_xSpeed < 0) {
		willGoPast = (m_x >= centerX && m_x + m_xSpeed <= centerX);
	}
	// If goes down
	else if (m_ySpeed > 0) {
		willGoPast = (m_y <= centerY && m_y + m_ySpeed >= centerY);
	}
	// If goes up
	else if (m_ySpeed < 0) {
		willGoPast = (m_y >= centerY && m_y + m_ySpeed <= centerY);
	}
	// If does not move
	else {
		willGoPast = (m_x == centerX && m_y == centerY);
	}

	return willGoPast;
}

void Character::moveOnCenter() {
	setX((m_maze->getColFromX(m_x) + 0.5) * Cell::SIZE);
	setY((m_maze->getRowFromY(m_y) + 0.5) * Cell::SIZE);
}
