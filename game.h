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

#ifndef __GAME_H
#define __GAME_H

#include <QTimer>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "maze.h"
#include "kapman.h"
#include "ghost.h"

/**
 * This class represents the game manager
 */
class Game : public QObject {

	Q_OBJECT

	private :

		/** Game timer */
		QTimer* m_timer;

		/** The scene containing the items to be displayed */
		QGraphicsScene* m_scene;
		
		/** Game Maze */
		Maze* m_maze;

		/** Main character */
		Kapman* m_kapman;
		
		/** Ghosts */
		QList<Ghost*> m_ghostList;
		
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
		 * Starts the game
		 */
		void start();

		/**
		 * Pauses the game
		 */
		void pause();

		/**
		 * @return the game scene
		 */
		QGraphicsScene* getScene() const;

	private:

		/**
		 * If the given character goes past the next center it mets during its
		 * next movement, then we put it right ON the center
		 * @param p_character the character which movement must be checked
		 * @return true if the character is put on a center, false otherwise
		 */
		bool onCenter(Kapman* p_character);

		/**
		 * Moves the given character on its current cell center
		 * @param p_character the character to move
		 */
		void moveOnCenter(Kapman* p_character);

		/**
		 * @param p_character the character we want to get the next cell
		 * @return the next cell the character will move on with its
		 *		   current direction
		 */
		Cell getNextCell(Kapman* p_character);

		/**
		 * @param p_character the character we want to get the next cell
		 * @return the next cell the character will move on with its
		 *		   asked direction
		 */
		Cell getAskedNextCell(Kapman* p_character);

	public slots:

		/**
		 * Called on key press event
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent* p_event);

		/**
		 * Called on each timer signal to update the game data
		 */
		void update();
};

#endif
