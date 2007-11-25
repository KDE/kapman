/* This file is part of Kapman.
   Created by Thomas Gallinari <tg8187@yahoo.fr>

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

#ifndef __KAPMANMAINWINDOW_H
#define __KAPMANMAINWINDOW_H

#include <KXmlGuiWindow>
#include <QGraphicsView>

#include "game.h"

/**
 * This class represents a main window for Kapman
 */
class KapmanMainWindow : public KXmlGuiWindow {

	Q_OBJECT

	private :
		
		/** The game view */
		QGraphicsView* m_view;

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

	public slots:

		/**
		 * Launches a new game
		 */
		void newGame();

		/**
		 * Closes the application
		 */
		void close();
};

#endif
