#ifndef __KAPMANMAINWINDOW_H
#define __KAPMANMAINWINDOW_H

#include <KXmlGuiWindow>
#include "game.h"

/**
 * This class represents a main window for Kapman
 */
class KapmanMainWindow : public KXmlGuiWindow {

	Q_OBJECT

	private :
		
		/** A Kapman Game */
		Game* m_game;
		
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
		 * Launches a new game
		 */
		void newGame();

		/**
		 * Closes the application
		 */
		void close();
};

#endif
