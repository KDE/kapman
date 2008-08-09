/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
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

#ifndef __GAMESCENE_H
#define __GAMESCENE_H

#include "game.h"
#include "elementitem.h"
#include "mazeitem.h"
#include "ghostitem.h"
#include "kapmanitem.h"

#include <QGraphicsScene>
#include <QList>

/**
 * @brief This class contains all the Game elements to be drawn on the screen by the GameView instance.
 */
class GameScene : public QGraphicsScene {

	Q_OBJECT
		
	private:

		/** The Game instance */
		Game* m_game;

		/** The MazeItem to be drawn */
		MazeItem* m_mazeItem;

		/** The KapmanItem to be drawn */
		KapmanItem* m_kapmanItem;

		/** The GhostItem of each Ghost to be drawn */
		QList<GhostItem*> m_ghostItems;
		
		/** The ElementItem to be drawn (each Pill and Energizers) */
		ElementItem*** m_elementItems;
		
		/** The Bonus ElementItem */
		ElementItem* m_bonusItem;

		/** The labels to be displayed during the game */
		QGraphicsTextItem* m_introLabel;
		QGraphicsTextItem* m_introLabel2;
		QGraphicsTextItem* m_newLevelLabel;
		QGraphicsTextItem* m_scoreLabel;
		QGraphicsTextItem* m_livesLabel;
		QGraphicsTextItem* m_levelLabel;
		QGraphicsTextItem* m_pauseLabel;
		
	public:

		/**
		 * Creates a new GameScene instance.
		 * @param p_game the Game instance whose elements must be contained in the GameScene in order to be drawn
		 */
		GameScene(Game* p_game);

		/**
		 * Deletes the Game instance.
		 */
		~GameScene();

		/**
		 * @return the Game instance
		 */
		Game* getGame() const;
		
	private slots:

		/**
		 * Updates the elements to be drawn on Game introduction.
		 * @param p_newLevel true a new level has begun, false otherwise
		 */
		void intro(const bool p_newLevel);
	
		/**
		 * Updates the elements to be drawn when the Game starts.
		 */
		void start();
		
		/**
		 * Updates the elements to be drawn considering the Game state (paused or running).
		 * @param p_pause if true the Game has been paused, if false the Game has been resumed
		 * @param p_fromUser if true the Game has been paused due to an action from the user
		 */
		void setPaused(const bool p_pause, const bool p_fromUser);
		
		/**
		 * Removes the Element at the given coordinates from the GameScene.
		 * @param p_x x-coordinate of the Element
		 * @param p_y y-coordinate of the Element
		 */
		void hideElement(const qreal p_x, const qreal p_y);
		
		/**
		 * Displays the Bonus.
		 */
		void displayBonus();
		
		/**
		 * Remove the Bonus from the GameScene.
		 */
		void hideBonus();
	
		/**
		 * Upadates the Game information labels.
		 * @param p_info the type of the information to be updated
		 */
		void updateInfo(const Game::InformationTypes p_info);
};

#endif

