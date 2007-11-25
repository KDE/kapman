#ifndef __GAMEVIEW_H
#define __GAMEVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>

/**
 * This class represents the view that visualizes the scene
 */
class GameView : public QGraphicsView {

	Q_OBJECT
		
	public:

		/**
		 * Creates a new GameView instance
		 * @param p_scene the scene to visualize
		 */
		GameView(QGraphicsScene* p_scene);

		/**
		 * Deletes the GameView instance
		 */
		~GameView();

	protected:

		/**
		 * Called on window resizing
		 * @param event the resize event
		 */
		void resizeEvent(QResizeEvent* p_event);

		/**
		 * Called on key press
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent* p_event);

	signals:

		/**
		 * Emitted on key press
		 * @param p_event the key press event
		 */
		void keyPressed(QKeyEvent* p_event);
};

#endif
