/**
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
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

#ifndef __KAPMANMAINWINDOW_H
#define __KAPMANMAINWINDOW_H

#include <KXmlGuiWindow>
#include <QGraphicsView>

#include "game.h"
#include "gameview.h"

/**
 * This class represents a main window for Kapman
 */
class KapmanMainWindow : public KXmlGuiWindow {

	Q_OBJECT

	private :
		
		/** The game view */
		GameView* m_view;

		/** A Kapman game */
		Game* m_game;
		
	public:

		/**
		 * Creates a new KapmanMainWindow instance
		 */
		KapmanMainWindow();

		/**
		 * Deletes the KapmanMainWindow instance
		 */
		~KapmanMainWindow();

	private:

		/**
		 * Initializes a game
		 */
		void initGame();

	public slots:

		/**
		 * Launches a new game
		 * @param gamefinished  : at true when there isn't more lifes, print the score,  at false ask to confirm to quit the game.
		 */
		void newGame(bool gamefinished);

		/**
		 * Closes the application
		 */
		void close();
};

#endif
