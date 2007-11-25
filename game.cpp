#include <KStandardDirs>
#include "game.h"
#include "mazeview.h"
#include "kapmanview.h"

Game::Game() {
	m_scene = new QGraphicsScene();
	m_maze = new Maze();
	m_kapman = new Kapman();
	m_scene->addItem(new MazeView(
		KStandardDirs::locate("appdata", "dessin_test.svg")));
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
