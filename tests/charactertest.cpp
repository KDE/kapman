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
#include "charactertest.h"
#include "character.h"

void CharacterTest::testCharacter() {
	Character * cha = new Character(0.0, 0.0);
	
	QCOMPARE(cha->getX(), 0.0);
	QCOMPARE(cha->getY(), 0.0);
	QCOMPARE(cha->getXSpeed(), 0.0);
	QCOMPARE(cha->getYSpeed(), 0.0);
}

void CharacterTest::testMove() {	
	
	Character * cha = new Character(0.0, 0.0);
	
	qreal chaX = cha->getX();	// The x coordinate before calling move()
	qreal chaY = cha->getY();	// The y coordinate before calling move()
	
	// Spy on moved signal
	QSignalSpy viewUpdate(cha, SIGNAL(moved(qreal, qreal)));
	
	cha->setXSpeed(2);
	cha->move();
	
	// test of the new coordinates
	QCOMPARE(cha->getX(), chaX + 2.0);
	QCOMPARE(cha->getY(), chaY);
	
	cha->move();
	
	// test of the new coordinates
	QCOMPARE(cha->getX(), chaX + 4.0);
	QCOMPARE(cha->getY(), chaY);
	
	cha->setYSpeed(-3.0);
	cha->setXSpeed(0.0);
	cha->move();
	
	// test of the new coordinates
	QCOMPARE(cha->getX(), chaX + 4.0);
	QCOMPARE(cha->getY(), chaY - 3.0);
	
	// results of the spy viewUpdate
	QCOMPARE(viewUpdate.count(), 3);
	
	QCOMPARE(viewUpdate.at(0).at(0).toDouble(), chaX + 2.0);
	QCOMPARE(viewUpdate.at(0).at(1).toDouble(), chaY);
	
	QCOMPARE(viewUpdate.at(1).at(0).toDouble(), chaX + 4.0);
	QCOMPARE(viewUpdate.at(1).at(1).toDouble(), chaY);
	
	QCOMPARE(viewUpdate.at(2).at(0).toDouble(), chaX + 4.0);
	QCOMPARE(viewUpdate.at(2).at(1).toDouble(), chaY - 3.0);
}
