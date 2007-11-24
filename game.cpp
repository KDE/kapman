#include <KStandardDirs>
#include "game.h"
#include "mazeview.h"

Game::Game() {
	m_scene = new QGraphicsScene();
	m_maze = new Maze();
	m_scene->addItem(new MazeView(
		KStandardDirs::locate("appdata", "dessin_test.svg")));
}
	
Game::~Game() {
	delete m_scene;
	delete m_maze;
}
		
QGraphicsScene * Game::getScene() const {
	return m_scene;
}
