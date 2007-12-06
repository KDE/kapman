/* This file is part of Kapman.
   Created by Pierre-Benoît Besse <besse.pb@gmail.com>

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
#include "mazeitem.h"
#include "kapmanitem.h"
#include "ghostitem.h"

Game::Game() {
	m_scene = new QGraphicsScene();
	m_maze = new Maze();
	m_kapman = new Kapman();
	m_ghostList.append(new Ghost(260.0, 215.0, "redGhost_test.svg"));
	m_ghostList.append(new Ghost(260.0, 275.0, "redGhost_test.svg"));
	m_ghostList.append(new Ghost(222.0, 275.0, "redGhost_test.svg"));
	m_ghostList.append(new Ghost(298.0, 275.0, "redGhost_test.svg"));
	
	// Add the items to the scene
	m_scene->addItem(new MazeItem(
		KStandardDirs::locate("appdata", "kapmanMaze.svg")));
	m_scene->addItem(new KapmanItem(
		m_kapman, KStandardDirs::locate("appdata", "kapman_test.svg")));
	for(int i=0; i<m_ghostList.size(); i++) {
		m_scene->addItem(new GhostItem(
			m_ghostList.at(i), KStandardDirs::locate(
				"appdata", m_ghostList.at(i)->getImageURL())));
	}
	
	// Start the timer to move the characters regulary
	m_timer = new QTimer(this);
	m_timer->setInterval(15); // 60 FPS
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
}

Game::~Game() {
	delete m_scene;
	delete m_maze;
	delete m_kapman;
}

void Game::start() {
	m_timer->start();
}

void Game::pause() {
	m_timer->stop();
}

QGraphicsScene* Game::getScene() const {
	return m_scene;
}

void Game::keyPressEvent(QKeyEvent* p_event) {
	// WARNING : This is a test, not the final behaviour !
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
		default:
			break;
	}
}

void Game::update() {
	m_kapman->move();
}
