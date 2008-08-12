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
#include "ghosttest.h"
#include "ghost.h"

void GhostTest::testGhost() {

	Maze * maze = new Maze();
	QString  itemImage("redGhost_test.svg");
	
	Ghost ghost(0.0, 0.0, itemImage, maze);
	
	QCOMPARE(ghost.getX(), 0.0);
	QCOMPARE(ghost.getY(), 0.0);
// 	QCOMPARE(ghost.getXSpeed(), -Ghost::SPEED);		// The ghost goes left at the begining
	QCOMPARE(ghost.getYSpeed(), 0.0);
	
	QCOMPARE(ghost.getImageURL(), QString("redGhost_test.svg"));
}

// void GhostTest::testGoUp() {
// 
// 	Ghost ghost (0.0, 0.0, "redGhost_test.svg");
// 
// 	ghost.goUp();
// 
// 	QCOMPARE(ghost.getXSpeed(), 0.0);	
// 	QCOMPARE(ghost.getYSpeed(), -Ghost::SPEED);
// }
// 
// void GhostTest::testGoDown() {
// 
// 	Ghost ghost (0.0, 0.0, "redGhost_test.svg");
// 
// 	ghost.goDown();
// 
// 	QCOMPARE(ghost.getXSpeed(), 0.0);	
// 	QCOMPARE(ghost.getYSpeed(), Ghost::SPEED);
// }
// 
// void GhostTest::testGoRight() {
// 
// 	Ghost ghost (0.0, 0.0, "redGhost_test.svg");
// 
// 	ghost.goRight();
// 
// 	QCOMPARE(ghost.getXSpeed(), Ghost::SPEED);	
// 	QCOMPARE(ghost.getYSpeed(), 0.0);
// }
// 
// void GhostTest::testGoLeft() {
// 
// 	Ghost ghost (0.0, 0.0, "redGhost_test.svg");
// 	
// 	ghost.goLeft();
// 
// 	QCOMPARE(ghost.getXSpeed(), -Ghost::SPEED);	
// 	QCOMPARE(ghost.getYSpeed(), 0.0);
// }

QTEST_KDEMAIN_CORE(GhostTest)
