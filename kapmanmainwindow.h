/*
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
#include <KDE/KScoreDialog>
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

		/** The highscores dialog */
		KScoreDialog* m_kScoreDialog;
		
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
		 * @param p_gameFinished true if a level was finished, false if a Game Over was reached
		 */
		void newGame(bool p_gameFinished);

		/**
		 * Shows the highscores dialog
		 */
		void showHighscores();

		/**
		 * Closes the application
		 */
		void close();
};

#endif
