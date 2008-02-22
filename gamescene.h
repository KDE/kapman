/**
 * Copyright 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QGraphicsScene>
#include <QList>
#include "game.h"
#include "elementitem.h"
#include "mazeitem.h"
#include "characteritem.h"
#include "kapmanitem.h"

/**
 * This class represents the game Scene
 */
class GameScene : public QGraphicsScene {

	Q_OBJECT
		
	private:

		/** The game */
		Game* m_game;
		
		/** The list of the ElementItem Pills or Energizer*/
		ElementItem *** m_elementItemList;

		/** All the labels to be displayed during the game */
		QGraphicsTextItem* m_introLabel;
		QGraphicsTextItem* m_introLabel2;
		QGraphicsTextItem* m_scoreLabel;
		QGraphicsTextItem* m_livesLabel;
		QGraphicsTextItem* m_levelLabel;
		QGraphicsTextItem* m_pauseLabel;
		
		/** References on characters Item (needed to modify their zValue) */
		KapmanItem* m_kapmanItem;
		MazeItem* m_mazeItem;
		QList<CharacterItem*> m_ghostItemList;
		
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
		 * Inits the items on the scene
		 */
		void initItems();
	
		/**
		 * Display/remove the 'PAUSE' label when 'P' key is pressed
		 * @param gameIsPaused indicates if the game is paused or not
		 */
		void managePause(bool pauseGame);
		
		/**
		 * Remove the 'INTRO' label when a key is pressed
		 */
		void removeIntro();
		
		/**
		 * Remove the Pill or Energizer when the Kapman eat them
		 */
		void killElement(qreal, qreal);
	
		/**
		 * Upadate the score and lives labels
		 */
		void updateInfos();
};
