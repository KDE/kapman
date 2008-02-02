
/* This file is part of Kapman.
   Created by Thomas Gallinari <tg8187@yahoo.fr>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
*/

#include <KActionCollection>
#include <KStandardGameAction>
#include <KMessageBox>
#include <KLocalizedString>
#include "kapmanmainwindow.h"
#include "gameview.h"

KapmanMainWindow::KapmanMainWindow() {
	// Initialize the game
	initGame();
	// Set the window menus
	KStandardGameAction::gameNew(this, SLOT(newGame()), actionCollection());
	KStandardGameAction::quit(this, SLOT(close()), actionCollection());
	setupGUI();
	// Give the focus to the view
	m_view->setFocus();
}

KapmanMainWindow::~KapmanMainWindow() {
	delete m_game;
	delete m_view;
}

void KapmanMainWindow::initGame() {
	// Create the game
	m_game = new Game();
	// Create the view displaying the game scene
	m_view = new GameView(m_game);
	m_view->setBackgroundBrush(Qt::black);
	setCentralWidget(m_view);
}

void KapmanMainWindow::newGame() {
	// timer (is active if play is already beginning)
	bool timer = m_game->getTimer()->isActive();
	if(timer)
		m_game->pause();
	if(KMessageBox::warningYesNo(this,
		ki18n("Are you sure you want to quit the current game ?").toString(),
		ki18n("New game").toString()) == KMessageBox::Yes) {
		// Start a new game
		delete m_game;
		delete m_view;
		initGame();
	}
	else {
		if(timer)
			m_game->start();
	}
	// Give the focus to the view
	m_view->setFocus();
}

void KapmanMainWindow::close() {
	// timer (is active if play is already beginning)
	bool timer = m_game->getTimer()->isActive();
	if(timer)
		m_game->pause();
	if(KMessageBox::warningYesNo(this,
		ki18n("Are you sure you want to quit Kapman ?").toString(),
		ki18n("Quit").toString()) == KMessageBox::Yes) {
		// Call the close() function of the parent class
		KXmlGuiWindow::close();
	}
	else {
		if(timer)
			m_game->start();
	}
	
}
