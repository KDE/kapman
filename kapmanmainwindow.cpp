/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Pierre-Benoit Bessse <besse@gmail.com>
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

#include "kapmanmainwindow.h"
#include "gameview.h"

#include <KActionCollection>
#include <KDE/KStandardGameAction>
#include <KMessageBox>
#include <KLocalizedString>

KapmanMainWindow::KapmanMainWindow() {
	// Initialize the game
	initGame();

	// Set the window menus
	KStandardGameAction::gameNew(this, SLOT(newGame(bool)), actionCollection());
	KStandardGameAction::highscores(this, SLOT(showHighscores()), actionCollection());
	KStandardGameAction::quit(this, SLOT(close()), actionCollection());
	
	// Initialize the KGameDifficulty singleton
	KGameDifficulty::init(this, this, SLOT(difficultyChanged()));
 	KGameDifficulty::addStandardLevel(KGameDifficulty::Easy);
 	KGameDifficulty::addStandardLevel(KGameDifficulty::Medium);
 	KGameDifficulty::addStandardLevel(KGameDifficulty::Hard);
 	KGameDifficulty::setRestartOnChange(KGameDifficulty::RestartOnChange);
 	// The default level
 	// TODO : Read this information in a config file
 	KGameDifficulty::setLevel(KGameDifficulty::Medium);

	// KScoreDialog
	m_kScoreDialog = new KScoreDialog(KScoreDialog::Name | KScoreDialog::Score | KScoreDialog::Level, this);
	m_kScoreDialog->addField(KScoreDialog::Custom1, ki18n("Difficulty").toString(), "difficulty");
	
	setupGUI();
}

KapmanMainWindow::~KapmanMainWindow() {
	delete m_game;
	delete m_view;
	delete m_kScoreDialog;
}

void KapmanMainWindow::initGame() {
	// Create the game
	m_game = new Game(KGameDifficulty::level());
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
	else {
		// Build the score info
		QString score("Your Score : ");
		score += QString::number(m_game->getScore());
		
		// Display the score informations
		KMessageBox::information(this, ki18n(score.toAscii().data()).toString(), ki18n("Game Over").toString());	
		
		// Add the score to the highscores table
		KScoreDialog::FieldInfo scoreInfo;
		scoreInfo[KScoreDialog::Level].setNum(m_game->getLevel());
		scoreInfo[KScoreDialog::Score].setNum(m_game->getScore());
		scoreInfo[KScoreDialog::Custom1] = KGameDifficulty::levelString();
		// If the new score is a highscore then display the highscore dialog
		if (m_kScoreDialog->addScore(scoreInfo)) {
			// If the payer did not cheat, manage Highscores
			if(!m_game->isCheater()) {
				m_kScoreDialog->exec();
			} else {		// else, warn the player not to cheat again :)
				KMessageBox::information(this, ki18n("You cheated, no Highscore for you ;)").toString(), ki18n("Cheater !").toString());	
			}
		}
		
		// Start a new game
		delete m_game;
		delete m_view;
		initGame();
	}
}

void KapmanMainWindow::showHighscores() {
 	m_kScoreDialog->exec();
}

void KapmanMainWindow::difficultyChanged() {
	// Stop the current game and start a new game
	delete m_game;
	delete m_view;
	initGame();
}

void KapmanMainWindow::close() {
	// timer (is active if the game has already begun)
	bool timer = m_game->getTimer()->isActive();
	if(timer)
		m_game->pause();
	if(KMessageBox::warningYesNo(this,
		ki18n("Are you sure you want to quit Kapman ?").toString(),
		ki18nc("To quit Kapman", "Quit").toString()) == KMessageBox::Yes) {
		// Call the close() function of the parent class
		KXmlGuiWindow::close();
	}
	else {
		if(timer)
			m_game->start();
	}
	
}
