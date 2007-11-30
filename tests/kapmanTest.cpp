#include "kapmanTest.h"
#include "kapman.h"

void KapmanTest::testKapman() {

	Kapman kap;
	
	QCOMPARE(kap.getX(), 0);
	QCOMPARE(kap.getY(), 0);
	QCOMPARE(kap.getXSpeed(), 0);
	QCOMPARE(kap.getYSpeed(), 0);
}

void KapmanTest::testGoUp() {

	Kapman kap;
	int kapSpeed = kap.getSPEED();

	kap.goUp();

	QCOMPARE(kap.getXSpeed(), 0);	
	QCOMPARE(kap.getYSpeed(), -kapSpeed);
}

void KapmanTest::testGoDown() {

	Kapman kap;
	int kapSpeed = kap.getSPEED();

	kap.goDown();

	QCOMPARE(kap.getXSpeed(), 0);	
	QCOMPARE(kap.getYSpeed(), kapSpeed);
}

void KapmanTest::testGoRight() {

	Kapman kap;
	int kapSpeed = kap.getSPEED();

	kap.goRight();

	QCOMPARE(kap.getXSpeed(), kapSpeed);	
	QCOMPARE(kap.getYSpeed(), 0);
}

void KapmanTest::testGoLeft() {

	Kapman kap;
	int kapSpeed = kap.getSPEED();

	kap.goLeft();

	QCOMPARE(kap.getXSpeed(), -kapSpeed);	
	QCOMPARE(kap.getYSpeed(), 0);
}

void KapmanTest::testMove() {	
	
	Kapman * kap = new Kapman();
	
	int kapX = kap->getX();	// The x coordinate before calling move()
	int kapY = kap->getY();	// The y coordinate before calling move()
	
	// Spy on moved signal
	QSignalSpy viewUpdate(kap, SIGNAL(moved(int, int)));
	
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
	
	QCOMPARE(viewUpdate.at(0).at(0).toInt(), kapX);
	QCOMPARE(viewUpdate.at(0).at(1).toInt(), kapY - kap->getSPEED());
	
	QCOMPARE(viewUpdate.at(1).at(0).toInt(), kapX);
	QCOMPARE(viewUpdate.at(1).at(1).toInt(), kapY - 2*kap->getSPEED());
	
	QCOMPARE(viewUpdate.at(2).at(0).toInt(), kapX + kap->getSPEED());
	QCOMPARE(viewUpdate.at(2).at(1).toInt(), kapY - 2*kap->getSPEED());
}


QTEST_KDEMAIN_CORE(KapmanTest)
