/**
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	KStandardGameAction::gameNew(this, SLOT(newGame(bool)), actionCollection());
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
	// connect the signal startnewgame to the newgame slot
	connect(m_game, SIGNAL(startnewgame(bool)), this, SLOT(newGame(bool)));
	// Create the view displaying the game scene
	m_view = new GameView(m_game);
	m_view->setBackgroundBrush(Qt::black);
	setCentralWidget(m_view);
}

void KapmanMainWindow::newGame(bool gamefinished = false) {
	// timer (is active if the game has already begun)
	bool timer = m_game->getTimer()->isActive();
	if(timer)
		m_game->pause();

	if( gamefinished == false ){	
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
	}
	else{
		QString score ("Your Score : ");
		score += QString::number((double)m_game->getScore());
		KMessageBox::information(this,
			ki18n(score.toAscii().data()).toString(),
			ki18n("Game Over").toString());
			// Start a new game
			delete m_game;
			delete m_view;
			initGame();
	}
	// Give the focus to the view
	m_view->setFocus();
}

void KapmanMainWindow::close() {
	// timer (is active if the game has already begun)
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
