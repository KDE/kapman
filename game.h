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

		/** pause flag */
		bool m_isPaused;
		
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
		 
		/**
		 * @return m_isPaused attribute
		 */
		bool isPaused() const; 

		/**
		 * Manage the game pause when 'P' key is pressed
		 */
		void doPause();
		 
	signals:
	
		/**
		 * Signals to the scene to display/remove the 'PAUSE' label
		 * @param pauseGame indicates if the game is to be paused or not
		 */
		void managePause(bool pauseGame);
		
		/**
		 * Signals to the scene to remove the 'INTRO' label
		 */
		void removeIntro();

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
