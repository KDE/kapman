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
#ifndef KAPMAN_TEST_H
#define KAPMAN_TEST_H

#include <QObject>
#include <qtest_kde.h>

class KapmanTest : public QObject {

	Q_OBJECT

	private slots:
		
		/**
		 * Kapman constructor, initialize all coordinates (position and speed) to 0
		 * save the xSpeed to 2.0
		 */
		void testKapman();
		
		/** This function updates the kapman's real speed with it's asked speed */
// 		void testUpdateDirection();

		/**
		 * TODO
		 * This function returns the next cell the character will reach
		 * with its asked movement (kapman only)
		 */
// 		void testGetAskedNextCell();
		
		/** This function stop all kapman's movement (real speed AND asked speed) */
// 		void testStopMoving();

		/** This method tests the kapman movement in the maze */
		void testUpdateMove();
};

#endif
