#include "ghosttest.h"
#include "ghost.h"

void GhostTest::testGhost() {

	Ghost ghost(0.0, 0.0, "redGhost_test.svg");
	
	QCOMPARE(ghost.getX(), 0.0);
	QCOMPARE(ghost.getY(), 0.0);
	QCOMPARE(ghost.getXSpeed(), 0.0);
	QCOMPARE(ghost.getYSpeed(), 0.0);
}

void GhostTest::testGoUp() {

	Ghost ghost(0.0, 0.0, "redGhost_test.svg");
	qreal ghostSpeed = Ghost::SPEED;

	ghost.goUp();

	QCOMPARE(ghost.getXSpeed(), 0.0);	
	QCOMPARE(ghost.getYSpeed(), -ghostSpeed);
}

void GhostTest::testGoDown() {

	Ghost ghost(0.0, 0.0, "redGhost_test.svg");
	qreal ghostSpeed = Ghost::SPEED;

	ghost.goDown();

	QCOMPARE(ghost.getXSpeed(), 0.0);	
	QCOMPARE(ghost.getYSpeed(), ghostSpeed);
}

void GhostTest::testGoRight() {

	Ghost ghost(0.0, 0.0, "redGhost_test.svg");
	qreal ghostSpeed = Ghost::SPEED;

	ghost.goRight();

	QCOMPARE(ghost.getXSpeed(), ghostSpeed);	
	QCOMPARE(ghost.getYSpeed(), 0.0);
}

void GhostTest::testGoLeft() {

	Ghost ghost(0.0, 0.0, "redGhost_test.svg");
	qreal ghostSpeed = Ghost::SPEED;

	ghost.goLeft();

	QCOMPARE(ghost.getXSpeed(), -ghostSpeed);	
	QCOMPARE(ghost.getYSpeed(), 0.0);
}

void GhostTest::testMove() {	
	
	Ghost * ghost = new Ghost(0.0, 0.0, "redGhost_test.svg");
	
	qreal ghostX = ghost->getX();	// The x coordinate before calling move()
	qreal ghostY = ghost->getY();	// The y coordinate before calling move()
	
	// Spy on moved signal
	QSignalSpy viewUpdate(ghost, SIGNAL(moved(qreal, qreal)));
	
	ghost->goUp();
	ghost->move();
	
	// test of the new coordinates
	QCOMPARE(ghost->getX(), ghostX);
	QCOMPARE(ghost->getY(), ghostY - Ghost::SPEED);
	
	ghost->move();
	
	// test of the new coordinates
	QCOMPARE(ghost->getX(), ghostX);
	QCOMPARE(ghost->getY(), ghostY - 2*Ghost::SPEED);
	
	ghost->goRight();
	ghost->move();
	
	// test of the new coordinates
	QCOMPARE(ghost->getX(), ghostX + Ghost::SPEED);
	QCOMPARE(ghost->getY(), ghostY - 2*Ghost::SPEED);
	
	// results of the spy viewUpdate
	QCOMPARE(viewUpdate.count(), 3);
	
	QCOMPARE(viewUpdate.at(0).at(0).toDouble(), ghostX);
	QCOMPARE(viewUpdate.at(0).at(1).toDouble(), ghostY - Ghost::SPEED);
	
	QCOMPARE(viewUpdate.at(1).at(0).toDouble(), ghostX);
	QCOMPARE(viewUpdate.at(1).at(1).toDouble(), ghostY - 2*Ghost::SPEED);
	
	QCOMPARE(viewUpdate.at(2).at(0).toDouble(), ghostX + Ghost::SPEED);
	QCOMPARE(viewUpdate.at(2).at(1).toDouble(), ghostY - 2*Ghost::SPEED);
}
