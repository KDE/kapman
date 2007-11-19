#ifndef __GAME_H
#define __GAME_H

#include <QGraphicsScene>

#include "maze.h"

/**
 * This class represents the game manager
 */
class Game : public QObject {

	Q_OBJECT
	private :
		/** Game Scene */
		QGraphicsScene * m_scene;
		/** Game Maze */
		Maze * m_maze;
		
	public:

		/**
		 * Creates a new Game instance
		 */
		Game();

		/**
		 * Deletes the Game instance
		 */
		~Game();
		
		/**
		 * Game initialisation 
		 */
		void init();

		/**
		 * @return Scene
		 */
		QGraphicsScene * getScene();

	public slots:

};

#endif
