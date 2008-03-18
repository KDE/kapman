/* This file is part of Kapman.
   Created by Pierre-Benoit Besse <besse.pb@gmail.com>

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
#ifndef CHARACTER_TEST_H
#define CHARACTER_TEST_H

#include <QObject>
#include <qtest_kde.h>

class CharacterTest : public QObject {

	Q_OBJECT

	private slots:
	
		/** Ghost constructor, initialize all coordinates (position and speed) to 0 */
		void testCharacter();
		
		/** This function moves the character function of its speed on X and Y */
		void testMove();

		/**
		 * TODO
		 * This function return TRUE if the character will go past
		 * the center of a cell with it's  next movement, FALSE otherwise
		 */
// 		void testOnCenter();
		
		/** TODO This function put the character right on the center of the cell it's on */
// 		void testMoveOnCenter();
		
		/** 
		 * TODO
		 * This function returns the next cell the character will reach
		 * with its current movement
		 */
// 		void testGetNextCell();
		
		/**
		 * TODO
		 * This method returns true if the caller is in the same line than the character
		 * without wall between them and if it doesn't have to make a half turn
		 */
		void testIsInLineSight();

};

#endif
