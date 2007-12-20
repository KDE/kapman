/* This file is part of Kapman.
   Created by Alexandre Galinier <blluetroy@hotmail.com>

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
#ifndef GAME_TEST_H
#define GAME_TEST_H

#include <QObject>
#include <qtest_kde.h>

class GameTest : public QObject {

	Q_OBJECT

	private slots:
	
		/** Tests the constructor */
		void testGame();
		
		/**
		 * TODO
		 * This function return TRUE if the character will go past
		 * the center of a cell with it's  next movement, FALSE otherwise
		 */
		void testOnCenter();
		
		/** TODO This function put the character right on the center of the cell it's on */
		void testMoveOnCenter();
		
		/** 
		 * TODO
		 * This function returns the next cell the character will reach
		 * with its current movement
		 */
		void testGetNextCell();
		
		/**
		 * TODO
		 * This function returns the next cell the character will reach
		 * with its asked movement (kapman only)
		 */
		void testGetAskedNextCell();
		
		/** TODO This function manage all the kapman's movements */
		void testManageKapmanMove();
		
		/** TODO This function manage all the ghosts movments */
// 		void testManageGhostMove();
};

#endif
