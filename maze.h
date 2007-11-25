#ifndef __MAZE_H
#define __MAZE_H

#include <QObject>

/**
 * This class represents the maze of kapman
 */
class Maze : public QObject {

	Q_OBJECT
	
	public:

		/**
		 * Creates a new Maze instance
		 */
		Maze();

		/**
		 * Deletes the Maze instance
		 */
		~Maze();
		
		/**
		 * Initializes the maze from an XML file
		 */
		void init();
		
};

#endif
