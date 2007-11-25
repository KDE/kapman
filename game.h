#ifndef __GAME_H
#define __GAME_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include "maze.h"
#include "kapman.h"

/**
 * This class represents the game manager
 */
class Game : public QObject {

	Q_OBJECT

	private :

		/** The scene containing the items to be displayed */
		QGraphicsScene* m_scene;
		
		/** Game Maze */
		Maze* m_maze;

		/** Main character */
		Kapman* m_kapman;
		
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
		 * @return the game scene
		 */
		QGraphicsScene* getScene() const;

	public slots:

		/**
		 * Called on key press event
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent* p_event);
};

#endif
