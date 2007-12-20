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
#include "kapmantest.h"
#include "kapman.h"

/**
 * 		KAPMAN CLASS TESTS
 */
 
void KapmanTest::testKapman() {

	Kapman kap (0.0, 0.0);
	
	QCOMPARE(kap.getX(), 0.0);
	QCOMPARE(kap.getY(), 0.0);
	QCOMPARE(kap.getAskedXSpeed(), -Kapman::SPEED);		// The kapman goes left at the begining
}

void KapmanTest::testGoUp() {

	Kapman kap (0.0, 0.0);

	kap.goUp();

	QCOMPARE(kap.getAskedXSpeed(), 0.0);	
	QCOMPARE(kap.getAskedYSpeed(), -Kapman::SPEED);
}

void KapmanTest::testGoDown() {

	Kapman kap (0.0, 0.0);

	kap.goDown();

	QCOMPARE(kap.getAskedXSpeed(), 0.0);	
	QCOMPARE(kap.getAskedYSpeed(), Kapman::SPEED);
}

void KapmanTest::testGoRight() {

	Kapman kap (0.0, 0.0);

	kap.goRight();

	QCOMPARE(kap.getAskedXSpeed(), Kapman::SPEED);	
	QCOMPARE(kap.getAskedYSpeed(), 0.0);
}

void KapmanTest::testGoLeft() {

	Kapman kap (0.0, 0.0);
	
	kap.goLeft();

	QCOMPARE(kap.getAskedXSpeed(), -Kapman::SPEED);	
	QCOMPARE(kap.getAskedYSpeed(), 0.0);
}

void KapmanTest::testUpdateDirection() {
	Kapman kap (0.0, 0.0);
	
	kap.goLeft();
	QCOMPARE(kap.getXSpeed(), 0.0);	
	QCOMPARE(kap.getYSpeed(), 0.0);
	QCOMPARE(kap.getAskedXSpeed(), -Kapman::SPEED);	
	QCOMPARE(kap.getAskedYSpeed(), 0.0);
	
	kap.updateDirection();
	
	QCOMPARE(kap.getXSpeed(), -Kapman::SPEED);	
	QCOMPARE(kap.getYSpeed(), 0.0);
	QCOMPARE(kap.getAskedXSpeed(), 0.0);	
	QCOMPARE(kap.getAskedYSpeed(), 0.0);
}

void KapmanTest::testStopMoving() {
	Kapman kap (0.0, 0.0);
	
	kap.goDown();
	kap.updateDirection();
	kap.goRight();
	
	QCOMPARE(kap.getYSpeed(), Kapman::SPEED);
	QCOMPARE(kap.getAskedXSpeed(), Kapman::SPEED);
	
	kap.stopMoving();
	
	QCOMPARE(kap.getYSpeed(), 0.0);
	QCOMPARE(kap.getXSpeed(), 0.0);
	QCOMPARE(kap.getAskedXSpeed(), 0.0);
	QCOMPARE(kap.getAskedYSpeed(), 0.0);
}

// 
// 
// 
// /**
//  * This function is to be tested in Character now
//  */
// // void KapmanTest::testMove() {	
// // 	
// // 	Kapman * kap = new Kapman(0.0, 0.0);
// // 	
// // 	qreal kapX = kap->getX();	// The x coordinate before calling move()
// // 	qreal kapY = kap->getY();	// The y coordinate before calling move()
// // 	
// // 	// Spy on moved signal
// // 	QSignalSpy viewUpdate(kap, SIGNAL(moved(qreal, qreal)));
// // 	
// // 	kap->goUp();
// // 	kap->move();
// // 	
// // 	// test of the new coordinates
// // 	QCOMPARE(kap->getX(), kapX);
// // 	QCOMPARE(kap->getY(), kapY - Kapman::SPEED);
// // 	
// // 	kap->move();
// // 	
// // 	// test of the new coordinates
// // 	QCOMPARE(kap->getX(), kapX);
// // 	QCOMPARE(kap->getY(), kapY - 2*Kapman::SPEED);
// // 	
// // 	kap->goRight();
// // 	kap->move();
// // 	
// // 	// test of the new coordinates
// // 	QCOMPARE(kap->getX(), kapX + Kapman::SPEED);
// // 	QCOMPARE(kap->getY(), kapY - 2*Kapman::SPEED);
// // 	
// // 	// results of the spy viewUpdate
// // 	QCOMPARE(viewUpdate.count(), 3);
// // 	
// // 	QCOMPARE(viewUpdate.at(0).at(0).toDouble(), kapX);
// // 	QCOMPARE(viewUpdate.at(0).at(1).toDouble(), kapY - Kapman::SPEED);
// // 	
// // 	QCOMPARE(viewUpdate.at(1).at(0).toDouble(), kapX);
// // 	QCOMPARE(viewUpdate.at(1).at(1).toDouble(), kapY - 2*Kapman::SPEED);
// // 	
// // 	QCOMPARE(viewUpdate.at(2).at(0).toDouble(), kapX + Kapman::SPEED);
// // 	QCOMPARE(viewUpdate.at(2).at(1).toDouble(), kapY - 2*Kapman::SPEED);
// // }
// 
// QTEST_KDEMAIN_CORE(KapmanTest)
// 
