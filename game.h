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

#ifndef __GAME_H
#define __GAME_H

#include <QTimer>
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
		
		/** Game Maze */
		Maze* m_maze;

		/** Main character */
		Kapman* m_kapman;
		
		/** Ghosts */
		QList<Ghost*> m_ghostList;
		
		/** The possible directions for a character */
		enum Direction {
			NONE = 0,
			UP = -1,
			DOWN = 1,
			LEFT = -2,
			RIGHT = 2
		};
		
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
		 * Manage the game pause when 'P' key is pressed
		 */
		void doPause();
		
		/**
		 * @return the kapman model
		 */
		Kapman* getKapman() const;
		
		/**
		 * @return the list of ghosts models
		 */
		QList<Ghost*> getGhostList () const;
		
		/**
		 * @return the timer
		 */
		 QTimer * getTimer() const;
		 
		 /**
		  * @return the maze
		  */
		 Maze * getMaze() const;
	
// 	private:

		/**
		 * If the given character goes past the next center it mets during its
		 * next movement, then we put it right ON the center
		 * @param p_character the character which movement must be checked
		 * @return true if the character is put on a center, false otherwise
		 */
		bool onCenter(Character* p_character);

		/**
		 * Moves the given character on its current cell center
		 * @param p_character the character to move
		 */
		void moveOnCenter(Character* p_character);

		/**
		 * @param p_character the character we want to get the next cell
		 * @return the next cell the character will move on with its
		 *		   current direction
		 */
		Cell getNextCell(Character* p_character);

		/**
		 * @param p_character the character we want to get the next cell
		 * @return the next cell the character will move on with its
		 *		   asked direction
		 */
		Cell getAskedNextCell(Kapman* p_character);
		
		/**
		 * Manage the Kapman move
		 * @param p_kapman the kapman model we interact with
		 */
		 void manageKapmanMove(Kapman* p_kapman);
		 
		/**
		 * Manage a Ghost move
		 * @param p_ghost the ghost model we interact with
		 */
		 void manageGhostMove(Ghost* p_ghost);
		 
	signals:
	
		/**
		 * Signals to the scene to display/remove the 'PAUSE' label
		 * @param pauseGame indicates if the game is to be paused or not
		 */
		void managePause(bool pauseGame);

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
