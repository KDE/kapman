#ifndef KAPMAN_TEST_H
#define KAPMAN_TEST_H

#include <QObject>
#include <qtest_kde.h>

class KapmanTest : public QObject
{
	Q_OBJECT

	private slots:
	
		/** Kapman constructor, initialize all coordinates (position and speed) to 0 */
		void testKapman();
		
		/** This class changes the kapman's speed coordinates to make it move upward */
		void testGoUp();

		/** This class changes the kapman's speed coordinates to make it move downward */
		void testGoDown();

		/** This class changes the kapman's speed coordinates to make it move to the right */
		void testGoRight();

		/** This class changes the kapman's speed coordinates to make it move to the left */
		void testGoLeft();

		/** This class update the kapman position according to it's speed coordinates and asks the view to update*/
		void testMove();
};

#endif
