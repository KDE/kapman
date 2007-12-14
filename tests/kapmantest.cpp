#include "kapmantest.h"
#include "kapman.h"

void KapmanTest::testKapman() {

	Kapman kap (0.0, 0.0);
	
	QCOMPARE(kap.getX(), 0.0);
	QCOMPARE(kap.getY(), 0.0);
	QCOMPARE(kap.getXSpeed(), 0.0);
	QCOMPARE(kap.getYSpeed(), 0.0);
}

void KapmanTest::testGoUp() {

	Kapman kap (0.0, 0.0);
	qreal kapSpeed = Kapman::SPEED;

	kap.goUp();

	QCOMPARE(kap.getXSpeed(), 0.0);	
	QCOMPARE(kap.getYSpeed(), -kapSpeed);
}

void KapmanTest::testGoDown() {

	Kapman kap (0.0, 0.0);
	qreal kapSpeed = Kapman::SPEED;

	kap.goDown();

	QCOMPARE(kap.getXSpeed(), 0.0);	
	QCOMPARE(kap.getYSpeed(), kapSpeed);
}

void KapmanTest::testGoRight() {

	Kapman kap (0.0, 0.0);
	qreal kapSpeed = Kapman::SPEED;

	kap.goRight();

	QCOMPARE(kap.getXSpeed(), kapSpeed);	
	QCOMPARE(kap.getYSpeed(), 0.0);
}

void KapmanTest::testGoLeft() {

	Kapman kap (0.0, 0.0);
	qreal kapSpeed = Kapman::SPEED;

	kap.goLeft();

	QCOMPARE(kap.getXSpeed(), -kapSpeed);	
	QCOMPARE(kap.getYSpeed(), 0.0);
}

void KapmanTest::testMove() {	
	
	Kapman * kap = new Kapman(0.0, 0.0);
	
	qreal kapX = kap->getX();	// The x coordinate before calling move()
	qreal kapY = kap->getY();	// The y coordinate before calling move()
	
	// Spy on moved signal
	QSignalSpy viewUpdate(kap, SIGNAL(moved(qreal, qreal)));
	
	kap->goUp();
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX);
	QCOMPARE(kap->getY(), kapY - Kapman::SPEED);
	
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX);
	QCOMPARE(kap->getY(), kapY - 2*Kapman::SPEED);
	
	kap->goRight();
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX + Kapman::SPEED);
	QCOMPARE(kap->getY(), kapY - 2*Kapman::SPEED);
	
	// results of the spy viewUpdate
	QCOMPARE(viewUpdate.count(), 3);
	
	QCOMPARE(viewUpdate.at(0).at(0).toDouble(), kapX);
	QCOMPARE(viewUpdate.at(0).at(1).toDouble(), kapY - Kapman::SPEED);
	
	QCOMPARE(viewUpdate.at(1).at(0).toDouble(), kapX);
	QCOMPARE(viewUpdate.at(1).at(1).toDouble(), kapY - 2*Kapman::SPEED);
	
	QCOMPARE(viewUpdate.at(2).at(0).toDouble(), kapX + Kapman::SPEED);
	QCOMPARE(viewUpdate.at(2).at(1).toDouble(), kapY - 2*Kapman::SPEED);
}

QTEST_KDEMAIN_CORE(KapmanTest)

