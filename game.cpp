/* This file is part of Kapman.
   Created by Alexandre GALINIER <alex.galinier@hotmail.com>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
*/

#include <KStandardDirs>
#include <KDebug>

#include <cstdlib>
#include "time.h"

#include "game.h"

Game::Game() {
	m_maze = new Maze();
	m_kapman = new Kapman(Cell::SIZE * 14, Cell::SIZE * 17.5);
	m_ghostList.append(new Ghost(260.0, 215.0, "redGhost_test.svg"));
	m_ghostList.append(new Ghost(260.0, 275.0, "greenGhost_test.svg"));
	m_ghostList.append(new Ghost(222.0, 275.0, "blueGhost_test.svg"));
	m_ghostList.append(new Ghost(298.0, 275.0, "pinkGhost_test.svg"));

	// Start the timer to move the characters regulary
	m_timer = new QTimer(this);
	m_timer->setInterval(15); // 60 FPS
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
	
	// Put the red ghost on the center of its starting cell (FOR TESTS)
	moveOnCenter(m_ghostList[0]);
	
	// Initialize the random-number generator
	srand(time(NULL));
}

Game::~Game() {
	delete m_maze;
	delete m_kapman;
	for (int i = 0; i < m_ghostList.size(); i++) {
		delete m_ghostList[i];
	}
}

void Game::start() {
	m_timer->start();
}

void Game::pause() {
	m_timer->stop();
}

void Game::doPause() {
	// If the game isn't paused yet, we stop the timer
	if(m_timer->isActive()) {
		pause();

		// Signal to the scene to add a 'PAUSE' label
		emit(managePause(true));
		
		// TODO Disable arrows detection
		
	}
	// If the game is already paused, we restart the timer
	else {
		start();
		
		// Signal to the scene to remove the 'PAUSE' label
		emit(managePause(false));
		
		
		// TODO Enable arrows detection
		
	}
}

Kapman * Game::getKapman() const {
	return m_kapman;
}
		
QList<Ghost*> Game::getGhostList () const {
	return m_ghostList;
}

QTimer * Game::getTimer() const {
	return m_timer;
}

Maze * Game::getMaze() const {
	return m_maze;
}

bool Game::onCenter(Character* p_character) {
	// Get the current cell center coordinates
	qreal centerX = (m_maze->getColFromX(p_character->getX()) + 0.5) *
					Cell::SIZE;
	qreal centerY = (m_maze->getRowFromY(p_character->getY()) + 0.5) *
					Cell::SIZE;
	bool willGoPast = false;

	// Will the character go past the center of the cell it's on ?
	// If goes right
	if (p_character->getXSpeed() > 0) {
		willGoPast = (p_character->getX() <= centerX &&
					  p_character->getX() + p_character->getXSpeed() >=
					  centerX);
	}
	// If goes left
	else if (p_character->getXSpeed() < 0) {
		willGoPast = (p_character->getX() >= centerX &&
					  p_character->getX() + p_character->getXSpeed() <=
					  centerX);
	}
	// If goes down
	else if (p_character->getYSpeed() > 0) {
		willGoPast = (p_character->getY() <= centerY &&
					  p_character->getY() + p_character->getYSpeed() >=
					  centerY);
	}
	// If goes up
	else if (p_character->getYSpeed() < 0) {
		willGoPast = (p_character->getY() >= centerY &&
					  p_character->getY() + p_character->getYSpeed() <=
					  centerY);
	}
	// If does not move
	else {
		willGoPast = (p_character->getX() == centerX &&
					  p_character->getY() == centerY);
	}

	return willGoPast;
}

void Game::moveOnCenter(Character* p_character) {
	p_character->setX((m_maze->getColFromX(p_character->getX()) + 0.5) *
					Cell::SIZE);
	p_character->setY((m_maze->getRowFromY(p_character->getY()) + 0.5) *
					Cell::SIZE);
	
}

Cell Game::getNextCell(Character* p_character) {
	Cell nextCell;
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(p_character->getY());
	int curCellCol = m_maze->getColFromX(p_character->getX());

	// Get the next cell function of the character direction
	if (p_character->getXSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
	}
	else if (p_character->getXSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
	}
	else if (p_character->getYSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
	}
	else if (p_character->getYSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
	}

	return nextCell;
}

Cell Game::getAskedNextCell(Kapman* p_character) {
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(p_character->getY());
	int curCellCol = m_maze->getColFromX(p_character->getX());
	Cell nextCell;

	// Get the next cell function of the character asked direction
	if (p_character->getAskedXSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
	}
	else if (p_character->getAskedXSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
	}
	else if (p_character->getAskedYSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
	}
	else if (p_character->getAskedYSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
	}

	return nextCell;
}

void Game::manageKapmanMove(Kapman* p_kapman) {
	// If the kapman does not move
	if (p_kapman->getXSpeed() == 0 && p_kapman->getYSpeed() == 0) {
		// If the user asks for moving
		if (p_kapman->getAskedXSpeed() != 0 ||
			p_kapman->getAskedYSpeed() != 0) {
			// Check the next cell with the asked direction
			if (getAskedNextCell(p_kapman).getType() == Cell::CORRIDOR) {
					// Update the direction
					p_kapman->updateDirection();
					// Move the kapman
					p_kapman->move();
			}
		}
	}
	// If the kapman is already moving
	else {
		// If the kapman wants to go back it does not wait to be on a center
		if (p_kapman->getXSpeed() != 0 &&
			p_kapman->getAskedXSpeed() == -p_kapman->getXSpeed() ||
			p_kapman->getYSpeed() != 0 &&
			p_kapman->getAskedYSpeed() == -p_kapman->getYSpeed()) {
			// Go back
			p_kapman->updateDirection();
			// Move the kapman
			p_kapman->move();
		}
		else {
			// If the kapman gets on a cell center
			if (onCenter(p_kapman)) {
				// If there is an asked direction (but not a half-turn)
				if ((p_kapman->getAskedXSpeed() != 0 ||
					 p_kapman->getAskedYSpeed() != 0) &&
					(p_kapman->getAskedXSpeed() != p_kapman->getXSpeed() ||
					 p_kapman->getAskedYSpeed() != p_kapman->getYSpeed())) {
					// Check the next cell with the kapman asked direction
					if (getAskedNextCell(p_kapman).getType() ==
							Cell::CORRIDOR) {
						// Move the kapman on the cell center
						moveOnCenter(p_kapman);
						// Update the direction
						p_kapman->updateDirection();
					}
					else {
						// Check the next cell with the kapman current direction
						if (getNextCell(p_kapman).getType() != Cell::CORRIDOR) {
							// Move the kapman on the cell center
							moveOnCenter(p_kapman);
							// Stop moving
							p_kapman->stopMoving();
						}
						else {
							// Move the kapman
							p_kapman->move();
						}
					}
				}
				else {
					// Check the next cell with the kapman current direction
					if (getNextCell(p_kapman).getType() != Cell::CORRIDOR) {
						// Move the kapman on the cell center
						moveOnCenter(p_kapman);
						// Stop moving
						p_kapman->stopMoving();
					}
					else {
						// Move the kapman
						p_kapman->move();
					}
				}
			}
			else {
				// Move the kapman
				p_kapman->move();
			}
		}
	}
}

void Game::manageGhostMove(Ghost* p_ghost) {
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(p_ghost->getY());
	int curCellCol = m_maze->getColFromX(p_ghost->getX());
	
	// Indicates if the character hasn't any choice of direction save backward
	bool halfTurnRequired = true;
	
	// This list is to contain the different directions a ghost can choose when on a cell center
	QList<QPointF*> directionsList;
	kDebug() << "Test onCenter()";
	
	// If the ghost gets on a Cell center
	if( onCenter(p_ghost) ) {
		
		kDebug() << "X : " << p_ghost->getX();
		kDebug() << "Y : " << p_ghost->getY();
		kDebug() << "onCenter -> TRUE";
		
		kDebug() << "Col : " << curCellCol;
		kDebug() << "Row : " << curCellRow;
	
		// We retrieve all the directions the ghost can choose (save the half turn)
		// 
		if(m_maze->getCell(curCellRow, curCellCol +1).getType() == Cell::CORRIDOR) {
			if( !(p_ghost->getXSpeed()<0) ) {
				directionsList.append(new QPointF(Ghost::SPEED, 0.0));
				kDebug() << "Right cell is free";
				halfTurnRequired = false;
			}
		}
		if(m_maze->getCell(curCellRow +1, curCellCol).getType() == Cell::CORRIDOR) {
			if( !(p_ghost->getYSpeed()<0) ) {
				directionsList.append(new QPointF(0.0, Ghost::SPEED));
				kDebug() << "Down cell is free";
				halfTurnRequired = false;
			}
		}
		if(m_maze->getCell(curCellRow -1, curCellCol).getType() == Cell::CORRIDOR) {
			if( !(p_ghost->getYSpeed()>0) ) {
				directionsList.append(new QPointF(0.0, -Ghost::SPEED));
				kDebug() << "Up cell is free";
				halfTurnRequired = false;
			}
		}
		
		if(m_maze->getCell(curCellRow, curCellCol -1).getType() == Cell::CORRIDOR) {
			if( !(p_ghost->getXSpeed()>0) ) {
				directionsList.append(new QPointF(-Ghost::SPEED, 0.0));
				kDebug() << "Left cell is free";
				halfTurnRequired = false;
			}
		}
		
		// Random number generation to choose one of the directions
		int nb = int( double(rand()) / (double(RAND_MAX) + 1) * directionsList.size() );
		
		// If there is no directions in the lists, the character goes backward
		if(directionsList.size() == 0) {
			p_ghost->setXSpeed(-p_ghost->getXSpeed());	
			p_ghost->setYSpeed(-p_ghost->getYSpeed());
		}
		// If the choosed direction isn't forward, we move the ghost on the center of the cell and update the directions
		else if( (p_ghost->getXSpeed()!=0 && p_ghost->getXSpeed()!=directionsList[nb]->x()) 
				|| (p_ghost->getYSpeed()!=0 && p_ghost->getYSpeed()!=directionsList[nb]->y()) ) {
			moveOnCenter(p_ghost);
			p_ghost->setXSpeed(directionsList[nb]->x());
			p_ghost->setYSpeed(directionsList[nb]->y());
		}	
	}
	
	// We move the ghost
	p_ghost->move();
}

void Game::keyPressEvent(QKeyEvent* p_event) {
	switch (p_event->key()) {
		case Qt::Key_Up:
			m_kapman->goUp();
			break;
		case Qt::Key_Down:
			m_kapman->goDown();
			break;
		case Qt::Key_Right:
			m_kapman->goRight();
			break;
		case Qt::Key_Left:
			m_kapman->goLeft();
			break;
		case Qt::Key_P:
			doPause();
		default:
			break;
	}
}

void Game::update() {
	manageKapmanMove(m_kapman);
	manageGhostMove(m_ghostList[0]);
// 	for(int i=0; i<m_ghostList.size(); i++) {
// 		manageGhostMove(m_ghostList[i]);
// 	}
}
