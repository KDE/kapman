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
#ifndef GHOST_TEST_H
#define GHOST_TEST_H

#include <QObject>
#include <qtest_kde.h>

class GhostTest : public QObject {

	Q_OBJECT

	private slots:
	
		/** Ghost constructor, initialize all coordinates (position and speed) to 0 */
		void testGhost();
		
		/** This function changes the Ghost's speed coordinates to make it move upward */
		void testGoUp();

		/** This function changes the Ghost's speed coordinates to make it move downward */
		void testGoDown();

		/** This function changes the Ghost's speed coordinates to make it move to the right */
		void testGoRight();

		/** This function changes the Ghost's speed coordinates to make it move to the left */
		void testGoLeft();
};

#endif
