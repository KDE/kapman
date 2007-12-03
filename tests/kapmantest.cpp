#include "kapmanTest.h"
#include "kapman.h"

void KapmanTest::testKapman() {

	Kapman kap;
	
	QCOMPARE(kap.getX(), 0.0);
	QCOMPARE(kap.getY(), 0.0);
	QCOMPARE(kap.getXSpeed(), 0.0);
	QCOMPARE(kap.getYSpeed(), 0.0);
}

void KapmanTest::testGoUp() {

	Kapman kap;
	qreal kapSpeed = kap.getSPEED();

	kap.goUp();

	QCOMPARE(kap.getXSpeed(), 0.0);	
	QCOMPARE(kap.getYSpeed(), -kapSpeed);
}

void KapmanTest::testGoDown() {

	Kapman kap;
	qreal kapSpeed = kap.getSPEED();

	kap.goDown();

	QCOMPARE(kap.getXSpeed(), 0.0);	
	QCOMPARE(kap.getYSpeed(), kapSpeed);
}

void KapmanTest::testGoRight() {

	Kapman kap;
	qreal kapSpeed = kap.getSPEED();

	kap.goRight();

	QCOMPARE(kap.getXSpeed(), kapSpeed);	
	QCOMPARE(kap.getYSpeed(), 0.0);
}

void KapmanTest::testGoLeft() {

	Kapman kap;
	qreal kapSpeed = kap.getSPEED();

	kap.goLeft();

	QCOMPARE(kap.getXSpeed(), -kapSpeed);	
	QCOMPARE(kap.getYSpeed(), 0.0);
}

void KapmanTest::testMove() {	
	
	Kapman * kap = new Kapman();
	
	qreal kapX = kap->getX();	// The x coordinate before calling move()
	qreal kapY = kap->getY();	// The y coordinate before calling move()
	
	// Spy on moved signal
	QSignalSpy viewUpdate(kap, SIGNAL(moved(qreal, qreal)));
	
	kap->goUp();
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX);
	QCOMPARE(kap->getY(), kapY - kap->getSPEED());
	
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX);
	QCOMPARE(kap->getY(), kapY - 2*kap->getSPEED());
	
	kap->goRight();
	kap->move();
	
	// test of the new coordinates
	QCOMPARE(kap->getX(), kapX + kap->getSPEED());
	QCOMPARE(kap->getY(), kapY - 2*kap->getSPEED());
	
	// results of the spy viewUpdate
	QCOMPARE(viewUpdate.count(), 3);
	
	QCOMPARE(viewUpdate.at(0).at(0).toDouble(), kapX);
	QCOMPARE(viewUpdate.at(0).at(1).toDouble(), kapY - kap->getSPEED());
	
	QCOMPARE(viewUpdate.at(1).at(0).toDouble(), kapX);
	QCOMPARE(viewUpdate.at(1).at(1).toDouble(), kapY - 2*kap->getSPEED());
	
	QCOMPARE(viewUpdate.at(2).at(0).toDouble(), kapX + kap->getSPEED());
	QCOMPARE(viewUpdate.at(2).at(1).toDouble(), kapY - 2*kap->getSPEED());
}


QTEST_KDEMAIN_CORE(KapmanTest)
