/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Pierre-Benoit Bessse <besse@gmail.com>
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

#include "game.h"
#include "gameview.h"

#include <KXmlGuiWindow>
#include <QGraphicsView>
#include <KDE/KScoreDialog>
#include <KGameDifficulty>

/**
 * @brief This class enables to create the main window for Kapman.
 */
class KapmanMainWindow : public KXmlGuiWindow {

	Q_OBJECT

	private :
		
		/** The GameView instance that manages the game drawing and the collisions */
		GameView* m_view;

		/** The Game instance that manages the main loop and events */
		Game* m_game;

		/** The highscores dialog */
		KScoreDialog* m_kScoreDialog;
		
	public:

		/**
		 * Creates a new KapmanMainWindow instance.
		 */
		KapmanMainWindow();

		/**
		 * Deletes the KapmanMainWindow instance.
		 */
		~KapmanMainWindow();

	private slots:

		/**
		 * Initializes the KapmanMainWindow for a new game.
		 * Creates a new Game instance and a new GameView instance that displays the game.
		 */
		void initGame();

		/**
		 * Starts a new game.
		 * @param p_gameOver true if the game was over, false if a game is running
		 */
		void newGame(const bool p_gameOver = false);

		/**
		 * Shows the highscores dialog.
		 */
		void showHighscores();

		/**
		 * Shows the settings dialog.
		 */
		void showSettings();

		/**
		 * Loads the settings.
		 */
		void loadSettings();

		/**
		 * Closes the KapmanMainWindow.
		 */
		void close();
};

#endif

