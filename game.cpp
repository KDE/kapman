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
#include "mazeview.h"
#include "kapmanview.h"

Game::Game() {
	m_scene = new QGraphicsScene();
	m_maze = new Maze();
	m_kapman = new Kapman();
	m_scene->addItem(new MazeView(
		KStandardDirs::locate("appdata", "kapmanMaze.svg")));
	m_scene->addItem(new KapmanView(
		m_kapman, KStandardDirs::locate("appdata", "kapman_test.svg")));
}

Game::~Game() {
	delete m_scene;
	delete m_maze;
	delete m_kapman;
}

QGraphicsScene* Game::getScene() const {
	return m_scene;
}

void Game::keyPressEvent(QKeyEvent* p_event) {
	// WARNING : This is a test, not the final behaviour !
	switch (p_event->key()) {
		case Qt::Key_Up:
			m_kapman->goUp();
			m_kapman->move();
			break;
		case Qt::Key_Down:
			m_kapman->goDown();
			m_kapman->move();
			break;
		case Qt::Key_Right:
			m_kapman->goRight();
			m_kapman->move();
			break;
		case Qt::Key_Left:
			m_kapman->goLeft();
			m_kapman->move();
			break;
		default:
			break;
	}
}
