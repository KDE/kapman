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

#include "gametest.h"
#include "game.h"

void GameTest::testGame() {
// 	Game * game = new Game();
	
// 	QCOMPARE(game->getTimer()->isActive(), TRUE);
// 	QCOMPARE(game->getTimer()->interval(), 15);
}

void GameTest::testOnCenter() {

// 	Game * game = new Game();
// 	Kapman * kap = new Kapman(230.0, 230.0);		// Put the kapman right in the middle of a cell
// 	
// 	// The kapman goes right
// 	kap->setXSpeed(2.0);
// 	kap->setYSpeed(0.0);
// 	
// 	// The kapman is on the middle of a cell
// 	QCOMPARE(game->onCenter(kap), TRUE);
// 	
// 	// Put the kapman just before a center
// 	kap->setX(429.0);
// 	kap->setY(290.0);
// 	QCOMPARE(game->onCenter(kap), TRUE);
// 	
// 	// The kapman goes down
// 	kap->setXSpeed(0.0);
// 	kap->setYSpeed(2.0);
// 	
// 	// Makes the kapman reach exactly the middle of a cell with a speed of 2
// 	kap->setX(130.0);
// 	kap->setY(488.0);
// 	QCOMPARE(game->onCenter(kap), TRUE);
// 	
// 	// The kapman goes up
// 	kap->setXSpeed(0.0);
// 	kap->setYSpeed(-2.0);
// 	
// 	// Put the kapman too far away a cell to reach it
// 	kap->setX(130.0);
// 	kap->setY(493.0);
// 	QCOMPARE(game->onCenter(kap), FALSE);
// 	
// 	// The kapman goes left
// 	kap->setXSpeed(-2.0);
// 	kap->setYSpeed(0.0);
// 	
// 	// Put the kapman just after a cell center
// 	kap->setX(129.0);
// 	kap->setY(490.0);
// 	QCOMPARE(game->onCenter(kap), FALSE);
// 	
// 	// The kapman is stopped
// 	kap->setXSpeed(0.0);
// 	kap->setYSpeed(0.0);
// 	
// 	// Put the kapman right on a center
// 	kap->setX(130.0);
// 	kap->setY(490.0);
// 	QCOMPARE(game->onCenter(kap), TRUE);
}

void GameTest::testMoveOnCenter() {

// 	Game * game = new Game();
// 	Ghost * gho = new Ghost(37.0, 26.0, "redGhost_test.svg");
// 	
	// Put the ghost on a cell
	
}

void GameTest::testGetNextCell() {
	
}

void GameTest::testGetAskedNextCell() {
	
}

void GameTest::testManageKapmanMove() {

}
