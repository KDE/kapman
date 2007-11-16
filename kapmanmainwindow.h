#ifndef __KAPMANMAINWINDOW_H
#define __KAPMANMAINWINDOW_H

#include <KXmlGuiWindow>

/**
 * This class represents a main window for Kapman
 */
class KapmanMainWindow : public KXmlGuiWindow {

	Q_OBJECT

	public:

		/**
		 * Creates a new KapmanMainWindow instance
		 */
		KapmanMainWindow();

		/**
		 * Deletes the KapmanMainWindow instance
		 */
		~KapmanMainWindow();

	public slots:

		/**
		 * Asks for a new game
		 */
		void askNewGame();

		/**
		 * Asks for exit
		 */
		void askClose();

		/**
		 * Launches a new game
		 */
		void newGame();
};

#endif
