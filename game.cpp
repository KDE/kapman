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

#include "game.h"

Game::Game() {
	m_maze = new Maze();
	m_kapman = new Kapman(Cell::SIZE * 14, Cell::SIZE * 17.5, m_maze);
	m_ghostList.append(new Ghost(Cell::SIZE * 14, Cell::SIZE * 11.5, "redGhost_test.svg", m_maze));
	m_ghostList.append(new Ghost(Cell::SIZE * 12, Cell::SIZE * 14.5, "greenGhost_test.svg", m_maze));
	m_ghostList.append(new Ghost(Cell::SIZE * 14, Cell::SIZE * 14.5, "blueGhost_test.svg", m_maze));
	m_ghostList.append(new Ghost(Cell::SIZE * 16, Cell::SIZE * 14.5, "pinkGhost_test.svg", m_maze));

	// Connects the kapman to the "kapmanDeath" slot
	connect(m_kapman, SIGNAL(lifeLost()), this, SLOT(kapmanDeath()));

	// Start the timer to move the characters regulary
	m_timer = new QTimer(this);
	m_timer->setInterval(15); // 60 FPS
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
	
	initCharactersPosition();
}

Game::~Game() {
	delete m_maze;
	delete m_kapman;
	delete m_timer;
	for (int i = 0; i < m_ghostList.size(); i++) {
		delete m_ghostList[i];
	}
}

void Game::start() {
	m_timer->start();
	m_isPaused = false;
}

void Game::pause() {
	m_timer->stop();
	m_isPaused = true;
}

void Game::doPause() {
	// If the game isn't paused yet, we stop the timer
	if(!m_isPaused) {
		pause();

		// Signal to the scene to add a 'PAUSE' label
		emit(managePause(true));
	}
	// If the game is already paused, we restart the timer
	else {
		start();
		
		// Signal to the scene to remove the 'PAUSE' label
		emit(managePause(false));
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

bool Game::isPaused() const {
	return m_isPaused;
}

/** Private */
void Game::initCharactersPosition() {
	// If the timer is stopped, it means that collisions are already being handled
	if(m_timer->isActive()) {
		
		// At the begining, the timer is stopped but the game isn't paused (to allow keyPressedEvent detection)
		m_timer->stop();
		m_isPaused = false;		
		
		// Initialize ghosts position
		// TODO Mettre un attribut "initialPosition" dans chaque character, initialisé à partir du XML
		m_ghostList[0]->setX(Cell::SIZE * 14);
		m_ghostList[0]->setY(Cell::SIZE * 11.5);
		m_ghostList[1]->setX(Cell::SIZE * 12);
		m_ghostList[1]->setY(Cell::SIZE * 14.5);
		m_ghostList[2]->setX(Cell::SIZE * 14);
		m_ghostList[2]->setY(Cell::SIZE * 14.5);
		m_ghostList[3]->setX(Cell::SIZE * 16);
		m_ghostList[3]->setY(Cell::SIZE * 14.5);
		
		// Initialize the kapman position
		m_kapman->setX(Cell::SIZE * 14);
		m_kapman->setY(Cell::SIZE * 17.5);
	}
}

void Game::keyPressEvent(QKeyEvent* p_event) {
	// At the beggining, we start the timer when a key is pressed
	if(!m_isPaused && !m_timer->isActive()) {
		m_timer->start();
		emit(removeIntro());
	}
	// Behaviour when the game has begun
	switch (p_event->key()) {
		case Qt::Key_Up:
			if(!m_isPaused) {
				m_kapman->goUp();
			}
			break;
		case Qt::Key_Down:
			if(!m_isPaused) {
				m_kapman->goDown();
			}
			break;
		case Qt::Key_Right:
			if(!m_isPaused) {
				m_kapman->goRight();
			}
			break;
		case Qt::Key_Left:
			if(!m_isPaused) {
				m_kapman->goLeft();
			}
			break;
		case Qt::Key_P:
			doPause();
		default:
			break;
	}
}

/** SLOTS */
void Game::update() {
	int curKapmanRow, curKapmanCol;
	
	//check if the kapman is in the line of sight of a ghost
	curKapmanRow = m_maze->getRowFromY(m_kapman->getY());
	curKapmanCol = m_maze->getColFromX(m_kapman->getX());
	
	for(int i=0; i<m_ghostList.size(); i++) {
		if(m_ghostList[i]->isInLineSight(m_kapman)) {
			m_ghostList[i]->updateMove(curKapmanRow, curKapmanCol);
		}
		else {
			m_ghostList[i]->updateMove();
		}
	}	
	m_kapman->updateMove();
}

void Game::kapmanDeath() {
	// Replace all characters to their initial positions
	initCharactersPosition();
}
