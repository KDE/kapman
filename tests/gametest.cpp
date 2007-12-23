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
#include "maze.h"
#include "cell.h"

void GameTest::testGame() {
	Game * game = new Game();
	
	QCOMPARE(game->getTimer()->isActive(), TRUE);
	QCOMPARE(game->getTimer()->interval(), 15);
}

void GameTest::testOnCenter() {

	Game * game = new Game();
	Kapman * kap = new Kapman(230.0, 230.0);		// Put the kapman right in the middle of a cell
	
	// The kapman goes right
	kap->setXSpeed(2.0);
	kap->setYSpeed(0.0);
	
	// The kapman is on the middle of a cell
	QCOMPARE(game->onCenter(kap), TRUE);
	
	// Put the kapman just before a center
	kap->setX(429.0);
	kap->setY(290.0);
	QCOMPARE(game->onCenter(kap), TRUE);
	
	// The kapman goes down
	kap->setXSpeed(0.0);
	kap->setYSpeed(2.0);
	
	// Makes the kapman reach exactly the middle of a cell with a speed of 2
	kap->setX(130.0);
	kap->setY(488.0);
	QCOMPARE(game->onCenter(kap), TRUE);
	
	// The kapman goes up
	kap->setXSpeed(0.0);
	kap->setYSpeed(-2.0);
	
	// Put the kapman too far away a cell to reach it
	kap->setX(130.0);
	kap->setY(493.0);
	QCOMPARE(game->onCenter(kap), FALSE);
	
	// The kapman goes left
	kap->setXSpeed(-2.0);
	kap->setYSpeed(0.0);
	
	// Put the kapman just after a cell center
	kap->setX(129.0);
	kap->setY(490.0);
	QCOMPARE(game->onCenter(kap), FALSE);
	
	// The kapman is stopped
	kap->setXSpeed(0.0);
	kap->setYSpeed(0.0);
	
	// Put the kapman right on a center
	kap->setX(130.0);
	kap->setY(490.0);
	QCOMPARE(game->onCenter(kap), TRUE);
}

void GameTest::testMoveOnCenter() {

	Game * game = new Game();
	Ghost * gho = new Ghost(37.0, 26.0, "redGhost_test.svg");
	
	// Put the ghost on the cell center and test
	game->moveOnCenter(gho);
	QCOMPARE(gho->getX(), 30.0);
	QCOMPARE(gho->getY(), 30.0);
	
	// Put the ghost on another cell, moveOnCenter and test
	gho->setX(210.0);
	gho->setY(175.0);
	game->moveOnCenter(gho);
	QCOMPARE(gho->getX(), 210.0);
	QCOMPARE(gho->getY(), 170.0);
	
	// Put the ghost right on a center, moveOnCenter and test
	gho->setX(70.0);
	gho->setY(290.0);
	game->moveOnCenter(gho);
	QCOMPARE(gho->getX(), 70.0);
	QCOMPARE(gho->getY(), 290.0);
	
	// Put the ghost right between 2 cells, moveOnCenter and test
	// CONVENTION : The function is supposed to choose the cell with the maximum of rows/cloumns
	// (right rather than left and down rather than up)
	gho->setX(40.0);
	gho->setY(30.0);
	game->moveOnCenter(gho);
	QCOMPARE(gho->getX(), 50.0);
	QCOMPARE(gho->getY(), 30.0);
}

void GameTest::testGetNextCell() {
	
	Game * game = new Game();
	Ghost * gho = new Ghost(43.0, 30.0, "redGhost_test.svg");	// ghost on a horizontal corridor
	
	// Makes the ghost go right and test
	gho->goRight();
	//QCOMPARE(game->getNextCell(gho), game->getMaze()->getCell(3, 1));
	
	// Makes the ghost go left and test
	gho->goLeft();
	//QCOMPARE(game->getNextCell(gho), game->getMaze()->getCell(1, 1));
	
	// Put the ghost on a vertical corridor
	gho->setX(130.0);
	gho->setY(65.0);
	
	// Makes the ghost go down and test
	gho->goDown();
	//QCOMPARE(game->getNextCell(gho), game->getMaze()->getCell(6, 4));
	
	// Makes the ghost go up and test
	gho->goUp();
	//QCOMPARE(game->getNextCell(gho), game->getMaze()->getCell(6, 2));
	
	
}

void GameTest::testGetAskedNextCell() {
	
}

void GameTest::testManageKapmanMove() {

}

QTEST_KDEMAIN_CORE(GameTest)
