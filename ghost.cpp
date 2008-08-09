/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>
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

#include <KDebug>
#include <QPointF>

#include <cstdlib>
#include "time.h"

const qreal Ghost::LOW_SPEED_INC = 0.05;
const qreal Ghost::MEDIUM_SPEED_INC = 0.1;
const qreal Ghost::HIGH_SPEED_INC = 0.15;
qreal Ghost::s_speed = Character::s_speed;
qreal Ghost::s_speedIncrease = Ghost::MEDIUM_SPEED_INC;

Ghost::Ghost(qreal p_x, qreal p_y, const QString & p_imageURL, Maze* p_maze) : Character(p_x, p_y, p_maze) {
	// Initialize the ghost attributes
	m_imageURL = p_imageURL;
	m_points = 200;
	m_type = Element::GHOST;
	m_state = Ghost::HUNTER;
	m_speed = Ghost::s_speed;
	// Initialize the random-number generator
	srand(time(NULL));
	// Makes the ghost move as soon as the game is created
	goLeft();
	// Prey timer
	m_preyTimer = new QTimer(this);
	m_preyTimer->setInterval(10000);
	m_preyTimer->setSingleShot(true);
	connect(m_preyTimer, SIGNAL(timeout()), this, SLOT(endPreyState()));
}

Ghost::~Ghost() {
	delete m_preyTimer;
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
	// Flag wether the ghost has no choice but go back
	bool halfTurnRequired = true;
	// Contains the different directions a ghost can choose when on a cell center
	QList<QPointF> directionsList;
	int nb = 0;
	
	// If the ghost is not "eaten"
	if (m_state != Ghost::EATEN) {	
		// If the ghost gets on a Cell center
		if (onCenter()) {
			// We retrieve all the directions the ghost can choose (save the half turn)
			if (m_maze->getCell(curCellRow, curCellCol + 1).getType() == Cell::CORRIDOR || 
					(m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
					 m_maze->getCell(curCellRow, curCellCol + 1).getType() == Cell::GHOSTCAMP)) {
				if (m_xSpeed >= 0) {
					directionsList.append(QPointF(m_speed, 0.0));
					halfTurnRequired = false;
				}
			}
			if (m_maze->getCell(curCellRow + 1, curCellCol).getType() == Cell::CORRIDOR ||
					(m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
					 m_maze->getCell(curCellRow + 1, curCellCol).getType() == Cell::GHOSTCAMP)) {
				if (m_ySpeed >= 0) {
					directionsList.append(QPointF(0.0, m_speed));
					halfTurnRequired = false;
				}
			}
			if (m_maze->getCell(curCellRow - 1, curCellCol).getType() == Cell::CORRIDOR ||
					(m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
					 m_maze->getCell(curCellRow - 1, curCellCol).getType() == Cell::GHOSTCAMP)) {
				if (m_ySpeed <= 0) {
					directionsList.append(QPointF(0.0, -m_speed));
					halfTurnRequired = false;
				}
			}
			if (m_maze->getCell(curCellRow, curCellCol - 1).getType() == Cell::CORRIDOR ||
					(m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
					 m_maze->getCell(curCellRow, curCellCol - 1).getType() == Cell::GHOSTCAMP)) {
				if (m_xSpeed <= 0) {
					directionsList.append(QPointF(-m_speed, 0.0));
					halfTurnRequired = false;
				}
			}
			// Random number generation to choose one of the directions
			nb = int(double(rand()) / (double(RAND_MAX) + 1) * directionsList.size());
			// If there is no directions in the list, the character goes backward
			if (directionsList.size() == 0) {
				m_xSpeed = -m_xSpeed;	
				m_ySpeed = -m_ySpeed;
			} else if ((m_xSpeed != 0 && m_xSpeed != directionsList[nb].x()) ||
					   (m_ySpeed != 0 && m_ySpeed != directionsList[nb].y())) {		// If the chosen direction isn't forward
				// We move the ghost on the center of the cell and update the directions
				moveOnCenter();
				m_xSpeed = directionsList[nb].x();
				m_ySpeed = directionsList[nb].y();
			}
		}
		// We move the ghost
		move();
	} else {	// If the ghost has been eaten
		if (onCenter()) {
			// If the ghost has not reached the camp yet
			if (m_pathToCamp.size() != 0) {
				// Go to the next cell to the camp
				updateMove(m_pathToCamp.first().y(), m_pathToCamp.first().x());
				// Remove the cell the ghost has reached from the path
				m_pathToCamp.removeFirst();
			} else {
				// If the ghost is not at home (that means it has just been eaten)
				if (curCellRow != Maze::GHOST_RESURRECT_CELL.y() || curCellCol != Maze::GHOST_RESURRECT_CELL.x()) {
					// Compute the path to go back to the camp
					m_pathToCamp = m_maze->getPathToGhostCamp(curCellRow, curCellCol);
					updateMove(m_pathToCamp.first().y(), m_pathToCamp.first().x());
				} else {	// The ghost has reached the ghost camp
					setState(Ghost::HUNTER);
				}
			}
		}
		move();
	}
}

void Ghost::updateMove(int p_row, int p_col) {
	// Get the current cell coordinates from the ghost coordinates
	int curGhostRow = m_maze->getRowFromY(m_y);
	int curGhostCol = m_maze->getColFromX(m_x);
	
	if (onCenter()) {
		if (curGhostRow == p_row) {
			if (p_col > curGhostCol) {
				m_xSpeed = m_speed;
				m_ySpeed = 0;
			} else {
				m_xSpeed = -m_speed;
				m_ySpeed = 0;
			}
		} else {	
			if (p_row > curGhostRow) {
				m_xSpeed = 0;
				m_ySpeed = m_speed;
			} else {
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

Ghost::State Ghost::getState() const {
	return m_state;
}

void Ghost::setState(Ghost::State p_state) {
	// Stop the prey timer if active
	if (m_preyTimer->isActive()) {
		m_preyTimer->stop();
	}
	// Change the state
	m_state = p_state;
	switch (m_state) {
		case Ghost::PREY:
			m_speed = Ghost::s_speed / 2;
			m_preyTimer->start();
			break;
		case HUNTER:
		case EATEN:
			m_speed = Ghost::s_speed;
			break;
	}
	emit(stateChanged());
}

void Ghost::doActionOnCollision(Kapman * p_kapman) {
	switch (m_state) {
		case Ghost::HUNTER:
			emit(lifeLost());
			break;
		case Ghost::PREY:
			emit(ghostEaten(this));
			break;
		case Ghost::EATEN:
			// Do nothing
			break;
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

void Ghost::endPreyState() {
	setState(Ghost::HUNTER);
}

