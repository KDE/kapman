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

#include <QGraphicsScene>
#include <QSize>

#include "game.h"

/**
 * This class represents the game Scene
 */
class GameScene : public QGraphicsScene {

	Q_OBJECT
		
	private:

		/** The game */
		Game* m_game;
	
		/** The PAUSE label to display when the game is paused */
		QGraphicsTextItem * pauseLabel;
		
		/** The INTRO label to display at the beginning */
		QGraphicsTextItem * introLabel;
		QGraphicsTextItem * introLabel2;
		
	public:

		/**
		 * Creates a new GameScene instance
		 *@param p_kapman the kapman model instance
		 *@param p_ghost the the lsit of ghost models instance
		 */
		GameScene(Game * p_game);

		/**
		 * Deletes the Game instance
		 */
		~GameScene();

		/**
		 * @return the game
		 */
		Game* getGame() const;
		
	public slots:
	
		/**
		 * Display/remove the 'PAUSE' label when 'P' key is pressed
		 * @param gameIsPaused indicates if the game is paused or not
		 */
		void managePause(bool pauseGame);
		
		/**
		 * Remove the 'INTRO' label when a key is pressed
		 */
		void removeIntro(); 
};
