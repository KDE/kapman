#include "game.h"
#include "mazeview.h"

Game::Game() {
	init();
}
	
Game::~Game() {

}

void Game::init() {
	m_scene = new QGraphicsScene();
	m_maze = new Maze();
	
	m_scene->addItem(new MazeView ("images/dessin_test.svg"));
}
		
QGraphicsScene * Game::getScene() {
	return m_scene;
}
