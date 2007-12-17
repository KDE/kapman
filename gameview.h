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

#ifndef __GAMEVIEW_H
#define __GAMEVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QSize>

#include "game.h"

/**
 * This class represents the view that visualizes the scene
 */
class GameView : public QGraphicsView {

	Q_OBJECT
	
	public:

		/**
		 * Creates a new GameView instance
		 */
		GameView(Game * p_game);

		/**
		 * Deletes the GameView instance
		 */
		~GameView();
		
		/**
		 * Called on window resizing
		 */
		void resizeManager();

	protected:

		/**
		 * Called on key press
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent * p_event);

	signals:

		/**
		 * Emitted on key press
		 * @param p_event the key press event
		 */
		void keyPressed(QKeyEvent * p_event);
};

#endif
