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
#include "charactertest.h"
#include "character.h"
#include "kapman.h"
#include "cell.h"

void CharacterTest::testCharacter() {

	Maze * maze = new Maze();
	Kapman * kap = new Kapman(0.0, 0.0, maze);
	
	// The Kapman has an initial xSpeed of 2.0
	QCOMPARE(kap->getX(), 0.0);
	QCOMPARE(kap->getY(), 0.0);
	QCOMPARE(kap->getXSpeed(), 2.0);
	QCOMPARE(kap->getYSpeed(), 0.0);
}

void CharacterTest::testMove() {	
	
	Maze * maze = new Maze();
	Kapman * kap = new Kapman(50.0, 30.0, maze);
	
	qreal kapX = kap->getX();	// The x coordinate before calling move()
	qreal kapY = kap->getY();	// The y coordinate before calling move()
	
	// Spy on moved signal
	QSignalSpy viewUpdate(kap, SIGNAL(moved(qreal, qreal)));
	
	kap->setXSpeed(2);
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX + 2.0);
	QCOMPARE(kap->getY(), kapY);
	
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX + 4.0);
	QCOMPARE(kap->getY(), kapY);
	
	kap->setYSpeed(-3.0);
	kap->setXSpeed(0.0);
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX + 4.0);
	QCOMPARE(kap->getY(), kapY - 3.0);
	
	// results of the spy viewUpdate
	QCOMPARE(viewUpdate.count(), 3);
	
	QCOMPARE(viewUpdate.at(0).at(0).toDouble(), kapX + 2.0);
	QCOMPARE(viewUpdate.at(0).at(1).toDouble(), kapY);
	
	QCOMPARE(viewUpdate.at(1).at(0).toDouble(), kapX + 4.0);
	QCOMPARE(viewUpdate.at(1).at(1).toDouble(), kapY);
	
	QCOMPARE(viewUpdate.at(2).at(0).toDouble(), kapX + 4.0);
	QCOMPARE(viewUpdate.at(2).at(1).toDouble(), kapY - 3.0);
}

// void CharacterTest::testOnCenter() {
// 
// 	Maze * maze = new Maze();
// 	Game * game = new Game();
// 	Kapman * kap = new Kapman(230.0, 230.0, maze);		// Put the kapman right in the middle of a cell
// 	
// 	// The kapman goes right
// 	kap->setXSpeed(2.0);
// 	kap->setYSpeed(0.0);
// 	
// 	// The kapman is on the middle of a cell
// 	QCOMPARE(kap->onCenter(), TRUE);
// 	
// 	// Put the kapman just before a center
// 	kap->setX(429.0);
// 	kap->setY(290.0);
// 	QCOMPARE(kap->onCenter(), TRUE);
// 	
// 	// The kapman goes down
// 	kap->setXSpeed(0.0);
// 	kap->setYSpeed(2.0);
// 	
// 	// Makes the kapman reach exactly the middle of a cell with a speed of 2
// 	kap->setX(130.0);
// 	kap->setY(488.0);
// 	QCOMPARE(kap->onCenter(), TRUE);
// 	
// 	// The kapman goes up
// 	kap->setXSpeed(0.0);
// 	kap->setYSpeed(-2.0);
// 	
// 	// Put the kapman too far away a cell to reach it
// 	kap->setX(130.0);
// 	kap->setY(493.0);
// 	QCOMPARE(kap->onCenter(), FALSE);
// 	
// 	// The kapman goes left
// 	kap->setXSpeed(-2.0);
// 	kap->setYSpeed(0.0);
// 	
// 	// Put the kapman just after a cell center
// 	kap->setX(129.0);
// 	kap->setY(490.0);
// 	QCOMPARE(kap->onCenter(), FALSE);
// 	
// 	// The kapman is stopped
// 	kap->setXSpeed(0.0);
// 	kap->setYSpeed(0.0);
// 	
// 	// Put the kapman right on a center
// 	kap->setX(130.0);
// 	kap->setY(490.0);
// 	QCOMPARE(kap->onCenter(), TRUE);
// }
// 
// void CharacterTest::testMoveOnCenter() {
// 
// 	Maze * maze = new Maze();
// 	Game * game = new Game();
// 	Ghost * gho = new Ghost(37.0, 26.0, "redGhost_test.svg", maze);
// 	
// 	// Put the ghost on the cell center and test
// 	gho->moveOnCenter();
// 	QCOMPARE(gho->getX(), 30.0);
// 	QCOMPARE(gho->getY(), 30.0);
// 	
// 	// Put the ghost on another cell, moveOnCenter and test
// 	gho->setX(210.0);
// 	gho->setY(175.0);
// 	gho->moveOnCenter();
// 	QCOMPARE(gho->getX(), 210.0);
// 	QCOMPARE(gho->getY(), 170.0);
// 	
// 	// Put the ghost right on a center, moveOnCenter and test
// 	gho->setX(70.0);
// 	gho->setY(290.0);
// 	gho->moveOnCenter();
// 	QCOMPARE(gho->getX(), 70.0);
// 	QCOMPARE(gho->getY(), 290.0);
// 	
// 	// Put the ghost right between 2 cells, moveOnCenter and test
// 	// CONVENTION : The function is supposed to choose the cell with the maximum of rows/cloumns
// 	// (right rather than left and down rather than up)
// 	gho->setX(40.0);
// 	gho->setY(30.0);
// 	gho->moveOnCenter();
// 	QCOMPARE(gho->getX(), 50.0);
// 	QCOMPARE(gho->getY(), 30.0);
// }
// 
// void CharacterTest::testGetNextCell() {
// 	
// 	Maze * maze = new Maze();
// 	Game * game = new Game();
// 	Ghost * gho = new Ghost(43.0, 30.0, "redGhost_test.svg", maze);	// ghost on a horizontal corridor
// 	
// 	// Makes the ghost go right and test
// 	gho->goRight();
// 	//QCOMPARE(gho->getNextCell(), game->getMaze()->getCell(3, 1));
// 	
// 	// Makes the ghost go left and test
// 	gho->goLeft();
// 	//QCOMPARE(gho->getNextCell(), game->getMaze()->getCell(1, 1));
// 	
// 	// Put the ghost on a vertical corridor
// 	gho->setX(130.0);
// 	gho->setY(65.0);
// 	
// 	// Makes the ghost go down and test
// 	gho->goDown();
// 	//QCOMPARE(gho->getNextCell(), game->getMaze()->getCell(6, 4));
// 	
// 	// Makes the ghost go up and test
// 	gho->goUp();
// 	//QCOMPARE(gho->getNextCell(), game->getMaze()->getCell(6, 2));
// }

void CharacterTest::testIsInLineSight() {
	//initialisation
// 	Maze * maze = new Maze();
// 	Kapman * characterBase = new Kapman(Cell::SIZE * 13, Cell::SIZE * 17, maze);
// 	Kapman * characterTested = new Kapman(0, 0, maze);
	
	//Same row and characterTested column > characterBase column
// 	characterTested->setX(Cell::SIZE * 14);
// 	characterTested->setY(Cell::SIZE * 17);
//   	characterBase->setXSpeed(Character::SPEED);
//  	characterBase->setYSpeed(0.0);
// 	QCOMPARE(characterBase->isInLineSight(characterTested), false);
	/*
	//Same row and characterTested column < characterBase column
	characterTested->setX(Cell::SIZE * 12);
	characterTested->setY(Cell::SIZE * 17.5);
	characterBase->setXSpeed(-Character::SPEED);
	characterBase->setYSpeed(0);
	
	QCOMPARE(characterBase->isInLineSight(characterTested), true);
	
	characterBase->setX(Cell::SIZE * 6);
	characterBase->setY(Cell::SIZE * 13);
	
	//Same column and characterTested row > characterBase row
	characterTested->setX(Cell::SIZE * 6);
	characterTested->setY(Cell::SIZE * 14);
	characterBase->setXSpeed(0);
	characterBase->setYSpeed(Character::SPEED);
	
	QCOMPARE(characterBase->isInLineSight(characterTested), true);
	
	//Same column and characterTested row < characterBase row
	characterTested->setX(Cell::SIZE * 6);
	characterTested->setY(Cell::SIZE * 12);
	characterBase->setXSpeed(0);
	characterBase->setYSpeed(-Character::SPEED);
	
	QCOMPARE(characterBase->isInLineSight(characterTested), true);
	
	//A wall between them
	characterTested->setX(Cell::SIZE * 14);
	characterTested->setY(Cell::SIZE * 11.5);
	characterBase->setX(Cell::SIZE * 14);
	characterBase->setY(Cell::SIZE * 17.5);
	characterBase->setXSpeed(0);
	characterBase->setYSpeed(-Character::SPEED);
	
	QCOMPARE(characterBase->isInLineSight(characterTested), false);*/
}

QTEST_KDEMAIN_CORE(CharacterTest)
