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

#ifndef __GAMEVIEW_H
#define __GAMEVIEW_H

#include "game.h"

#include <QGraphicsView>
#include <QKeyEvent>
#include <QSize>

/**
 * @brief This class manages the drawing of each element of the Game instance.
 * It creates a GameScene instance associated to the given Game instance in order to manage the elements to be drawn at each moment of the game.
 */
class GameView : public QGraphicsView {

	Q_OBJECT
	
	public:

		/**
		 * Creates a new GameView instance.
		 * @param p_game the Game instance whose elements have to be drawn
		 */
		GameView(Game* p_game);

		/**
		 * Deletes the GameView instance.
		 */
		~GameView();

		/**
		 * Resizes the items when the view is resized.
		 * @param p_event the resize event
		 */
		void resizeEvent(QResizeEvent* p_event);

	protected:

		/**
		 * Manages the player actions by hanlding the key press events.
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent* p_event);

		/**
		 * Pauses the game on focus lost.
		 * @param p_event the focus event
		 */
		void focusOutEvent(QFocusEvent* p_event);

	public slots:

		/**
		 * Loads the settings chosen by the user.
		 */
		void loadSettings();

	signals:

		/**
		 * Emitted on key press event for the Game instance
		 * @param p_event the key press event
		 */
		void keyPressed(QKeyEvent* p_event);
};

#endif

