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

#include "game.h"

Game::Game() {
	m_maze = new Maze();
	m_kapman = new Kapman(Cell::SIZE * 14, Cell::SIZE * 17.5, m_maze);
	m_ghostList.append(new Ghost(260.0, 215.0, "redGhost_test.svg", m_maze));
	m_ghostList.append(new Ghost(260.0, 275.0, "greenGhost_test.svg", m_maze));
	m_ghostList.append(new Ghost(222.0, 275.0, "blueGhost_test.svg", m_maze));
	m_ghostList.append(new Ghost(298.0, 275.0, "pinkGhost_test.svg", m_maze));

	// Start the timer to move the characters regulary
	m_timer = new QTimer(this);
	m_timer->setInterval(15); // 60 FPS
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
	m_isPaused = false;
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
	m_isPaused = false;
}

void Game::pause() {
	m_timer->stop();
	m_isPaused = true;
}

void Game::doPause() {
	// If the game isn't paused yet, we stop the timer
	if(m_timer->isActive()) {
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

void Game::keyPressEvent(QKeyEvent* p_event) {
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

void Game::update() {
	m_kapman->updateMove();
	for(int i=0; i<m_ghostList.size(); i++) {
		m_ghostList[i]->updateMove();
	}
}
