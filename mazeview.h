#ifndef __MAZEVIEW_H
#define __MAZEVIEW_H

#include <QGraphicsSvgItem>

/**
 * This class represents the view of the maze
 */
class MazeView : public QGraphicsSvgItem {
 
 	Q_OBJECT
 	
	public:

		/**
		 * Creates a new MazeView
		 * @param p_imagePath the path to the maze image
		 */
		MazeView(QString p_imagePath);

		/**
		 * Deletes the MazeView
		 */
		~MazeView();
};

#endif
