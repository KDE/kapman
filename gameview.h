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
		 * Called on view resizing
		 * @param p_event the resize event
		 */
		void resizeEvent(QResizeEvent* p_event);

	protected:

		/**
		 * Called on key press
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent * p_event);

		/**
		 * Overrides the QWidget method
		 */
		void focusOutEvent(QFocusEvent* p_evt);

	signals:

		/**
		 * Emitted on key press
		 * @param p_event the key press event
		 */
		void keyPressed(QKeyEvent * p_event);
};

#endif
