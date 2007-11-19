#ifndef __KAPMANMAINWINDOW_H
#define __KAPMANMAINWINDOW_H

#include <QString>
#include <KXmlGuiWindow>
#include "game.h"

/**
 * This class represents a main window for Kapman
 */
class KapmanMainWindow : public KXmlGuiWindow {

	Q_OBJECT
	private :
		
		/** A Kapman Game */
		Game * m_game;	
		
	public:

		/**
		 * Creates a new KapmanMainWindow instance
		 */
		KapmanMainWindow();

		/**
		 * Deletes the KapmanMainWindow instance
		 */
		~KapmanMainWindow();
		
		/**
		 * mainwindow initialisation 
		 */
		void init();

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
