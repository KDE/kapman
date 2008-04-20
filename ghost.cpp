/*
 * Copyright 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>
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

#include "ghost.h"
#include <cstdlib>
#include <QPointF>
#include "time.h"

const qreal Ghost::LOW_SPEED_INC = 0.05;
const qreal Ghost::MEDIUM_SPEED_INC = 0.1;
const qreal Ghost::HIGH_SPEED_INC = 0.15;
qreal Ghost::s_speed = Character::s_speed;
qreal Ghost::s_speedIncrease = Ghost::MEDIUM_SPEED_INC;

Ghost::Ghost(qreal p_x, qreal p_y, const QString & p_imageURL, Maze* p_maze) : Character(p_x, p_y, p_maze) {
	// Initialize the ghosts attributes
	m_imageURL = p_imageURL;
	m_points = 200;
	m_type = Element::GHOST;
	m_state = Ghost::HUNTER;
	m_speed = Ghost::s_speed;
	// Initialize the random-number generator
	srand(time(NULL));
	// Makes the ghost move as soon as the game is created
	goLeft();
}

Ghost::~Ghost() {

}

void Ghost::goUp() {
	m_xSpeed = 0;
 	m_ySpeed = -m_speed;
}
 
void Ghost::goDown() {
	m_xSpeed = 0;
	m_ySpeed = m_speed;
}

void Ghost::goRight() {
	m_xSpeed = m_speed;
	m_ySpeed = 0;
}

void Ghost::goLeft() {
	m_xSpeed = -m_speed;
	m_ySpeed = 0;
}

void Ghost::updateMove() {
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(m_y);
	int curCellCol = m_maze->getColFromX(m_x);
	
	// Indicates if the character hasn't any choice of direction save backward
	bool halfTurnRequired = true;
	
	// This list is to contain the different directions a ghost can choose when on a cell center
	QList<QPointF> directionsList;
	
	// If the ghost gets on a Cell center
	if( onCenter() ) {
	
		// We retrieve all the directions the ghost can choose (save the half turn)
		if(m_maze->getCell(curCellRow, curCellCol +1).getType() == Cell::CORRIDOR || (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP && m_maze->getCell(curCellRow, curCellCol +1).getType() == Cell::GHOSTCAMP)) {
			if(m_xSpeed >= 0) {
				directionsList.append(QPointF(m_speed, 0.0));
				halfTurnRequired = false;
			}
		}
		if(m_maze->getCell(curCellRow +1, curCellCol).getType() == Cell::CORRIDOR || (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP && m_maze->getCell(curCellRow +1, curCellCol).getType() == Cell::GHOSTCAMP)) {
			if(m_ySpeed >= 0) {
				directionsList.append(QPointF(0.0, m_speed));
				halfTurnRequired = false;
			}
		}
		if(m_maze->getCell(curCellRow -1, curCellCol).getType() == Cell::CORRIDOR || (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP && m_maze->getCell(curCellRow -1, curCellCol).getType() == Cell::GHOSTCAMP)) {
			if(m_ySpeed <= 0) {
				directionsList.append(QPointF(0.0, -m_speed));
				halfTurnRequired = false;
			}
		}
		
		if(m_maze->getCell(curCellRow, curCellCol -1).getType() == Cell::CORRIDOR || (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP && m_maze->getCell(curCellRow, curCellCol -1).getType() == Cell::GHOSTCAMP)) {
			if(m_xSpeed <= 0) {
				directionsList.append(QPointF(-m_speed, 0.0));
				halfTurnRequired = false;
			}
		}
		
		// Random number generation to choose one of the directions
		int nb = int( double(rand()) / (double(RAND_MAX) + 1) * directionsList.size() );
		
		// If there is no directions in the lists, the character goes backward
		if(directionsList.size() == 0) {
			m_xSpeed = -m_xSpeed;	
			m_ySpeed = -m_ySpeed;
		}
		// If the chosen direction isn't forward, we move the ghost on the center of the cell and update the directions
		else if( (m_xSpeed != 0 && m_xSpeed != directionsList[nb].x()) 
				|| (m_ySpeed !=0 && m_ySpeed != directionsList[nb].y())) {
			moveOnCenter();
			m_xSpeed = directionsList[nb].x();
			m_ySpeed = directionsList[nb].y();
		}	
	}
	
	// We move the ghost
	move();
}

void Ghost::updateMove(int p_row, int p_col) {
	// Get the current cell coordinates from the ghost coordinates
	int curGhostRow = m_maze->getRowFromY(m_y);
	int curGhostCol = m_maze->getColFromX(m_x);
	
	if(onCenter()) {
		if(curGhostRow == p_row) {
			if(p_col > curGhostCol) {
				m_xSpeed = m_speed;
				m_ySpeed = 0;
			}
			else {
				m_xSpeed = -m_speed;
				m_ySpeed = 0;
			}
		}
		else {	
			if(p_row > curGhostRow) {
				m_xSpeed = 0;
				m_ySpeed = m_speed;
			}
			else {
				m_xSpeed = 0;
				m_ySpeed = -m_speed;
			}
		}
	}
	// We move the ghost
	move();
}

QString Ghost::getImageURL() const  {
	return m_imageURL;
}

Ghost::GhostState Ghost::getState() const {
	return m_state;
}

void Ghost::setState(Ghost::GhostState p_state) {
	m_state = p_state;
	// Modify the speed
	if (m_state == Ghost::PREY) {
		// Reduce the speed
		m_speed = Ghost::s_speed / 2;
	}
	else if (m_state == Ghost::HUNTER) {
		// Reset the speed
		m_speed = Ghost::s_speed;
	}
	emit(stateChanged());
}

void Ghost::doActionOnCollision(Kapman * p_kapman) {
	if(getState() == Ghost::HUNTER) {
		emit(lifeLost());
	}
	else {
		emit(ghostEaten(this));
	}
}

void Ghost::initGhostsSpeed() {
	// Ghosts speed is characters speed
	Ghost::s_speed = Character::getCharactersSpeed();
	// Ghosts speed increase when level up
	if(Ghost::s_speed == LOW_SPEED) {
		s_speedIncrease = LOW_SPEED_INC;
	}
	if(Ghost::s_speed == MEDIUM_SPEED) {
		s_speedIncrease = MEDIUM_SPEED_INC;
	}
	if(Ghost::s_speed == HIGH_SPEED) {
		s_speedIncrease = HIGH_SPEED_INC;
	}
}

void Ghost::increaseGhostsSpeed() {
	Ghost::s_speed += Ghost::s_speedIncrease;
}	

