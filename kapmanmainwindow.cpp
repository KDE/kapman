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
#include "gamescene.h"
#include "settings.h"

#include <QPointer>
#include <KActionCollection>
#include <KStandardGameAction>
#include <KToggleAction>
#include <KMessageBox>
#include <KConfigDialog>
#include <KInputDialog>
#include <KLocale>
#include <KStatusBar>
#include <KgDifficulty>
#include <KScoreDialog>

#define USE_UNSTABLE_LIBKDEGAMESPRIVATE_API
#include <libkdegamesprivate/kgamethemeselector.h>

KapmanMainWindow::KapmanMainWindow() {
	// Initialize the game
	m_game = NULL;
	m_view = NULL;
	// Set the window menus
	KStandardGameAction::gameNew(this, SLOT(newGame(bool)), actionCollection());
	KStandardGameAction::highscores(this, SLOT(showHighscores()), actionCollection());
	KStandardAction::preferences(this, SLOT(showSettings()), actionCollection());
	KStandardGameAction::quit(this, SLOT(close()), actionCollection());
    	KAction* soundAction = new KToggleAction(i18n("&Play sounds"), this);
	soundAction->setChecked(Settings::sounds());
	actionCollection()->addAction( QLatin1String( "sounds" ), soundAction);
	connect(soundAction, SIGNAL(triggered(bool)), this, SLOT(setSoundsEnabled(bool)));
    	KAction* levelAction = new KAction(i18n("&Change level"), this);
	actionCollection()->addAction( QLatin1String( "level" ), levelAction);
	connect(levelAction, SIGNAL(triggered(bool)), this, SLOT(changeLevel()));
	// Add a statusbar to show level,score,lives information
	m_statusBar = statusBar();
	m_statusBar->insertItem(i18nc("Used to display the current level of play to the user", "Level: %1", 1), 1, 1);
	m_statusBar->insertItem(i18nc("Used to inform the user of their current score", "Score: %1", 0), 2, 1);
	m_statusBar->insertItem(i18nc("Used to tell the user how many lives they have left", "Lives: %1", initLives), 4, 1);

	
	// Initialize the KgDifficulty singleton
	Kg::difficulty()->addStandardLevelRange(
		KgDifficultyLevel::Easy, KgDifficultyLevel::Hard, //range
		KgDifficultyLevel::Medium //default
	);
	KgDifficultyGUI::init(this);
	connect(Kg::difficulty(), SIGNAL(currentLevelChanged(const KgDifficultyLevel*)), SLOT(initGame()));
	// Setup the window
	setupGUI();

	initGame();
}

KapmanMainWindow::~KapmanMainWindow() {
	delete m_statusBar;
	delete m_game;
	delete m_view;
}

void KapmanMainWindow::initGame() {
	// Create a new Game instance
	delete m_game;
	m_game = new Game();
	connect(m_game, SIGNAL(gameOver(bool)), this, SLOT(newGame(bool)));		// TODO Remove the useless bool parameter from gameOver()
	connect(m_game, SIGNAL(levelChanged(uint)), this, SLOT(displayLevel(uint)));
	connect(m_game, SIGNAL(scoreChanged(uint)), this, SLOT(displayScore(uint)));
	connect(m_game, SIGNAL(livesChanged(uint)), this, SLOT(displayLives(uint)));
	
	
	// Create a new GameView instance
	delete m_view;
	m_view = new GameView(m_game);
	m_view->setBackgroundBrush(Qt::black);
	setCentralWidget(m_view);
	m_view->setFocus();
	// For some reason, calling setFocus() immediately won't work after the
	// score dialog has been shown, so do it again after an eventloop run.
	QTimer::singleShot(0, m_view, SLOT(setFocus()));
	resetStatusBar();
}


void KapmanMainWindow::newGame(const bool gameOver) {
	bool gameRunning;		// True if the game is running (game timer is active), false otherwise
   
	gameRunning = m_game->getTimer()->isActive();
	// If the game is running
	if (gameRunning) {
		// Pause the game
		m_game->pause();
	}
	// If the game was not over
	if (!gameOver){	
		// Confirm before starting a new game
		if (KMessageBox::warningYesNo(this, i18n("Are you sure you want to quit the current game?"), i18n("New game")) == KMessageBox::Yes) {
			// Start a new game
			initGame();
		}
		else {
			// If the game was running
			if (gameRunning) {
				// Resume the game
				m_game->start();
			}
		}
	}
	else {
		// Display the score information
		KMessageBox::information(this, i18np("Your score is %1 point.", "Your score is %1 points.", m_game->getScore()), i18n("Game Over"));
		// manage Highscores only if player did not cheat
		if (m_game->isCheater()) {
			KMessageBox::information(this, i18n("You cheated, no Highscore for you ;)"), i18n("Cheater!"));	
		}
		else {
			// Add the score to the highscores table
			QPointer<KScoreDialog> dialog = new KScoreDialog(KScoreDialog::Name | KScoreDialog::Score | KScoreDialog::Level, this);
			dialog->initFromDifficulty(Kg::difficulty());
			KScoreDialog::FieldInfo scoreInfo;
			scoreInfo[KScoreDialog::Level].setNum(m_game->getLevel());
			scoreInfo[KScoreDialog::Score].setNum(m_game->getScore());
			// If the new score is a highscore then display the highscore dialog
			if (dialog->addScore(scoreInfo)) {
				dialog->exec();
			}
			delete dialog;
		}
		// Start a new game
		initGame();
	}
}

void KapmanMainWindow::changeLevel() {
	int newLevel = KInputDialog::getInteger(i18n("Change level"), i18nc("The number of the game level", "Level"), m_game->getLevel(), 1, 1000000, 1, 10, 0, this);
	if (newLevel > 0) {
		m_game->setLevel(newLevel);
	}
}

void KapmanMainWindow::showHighscores() {
	QPointer<KScoreDialog> dialog = new KScoreDialog(KScoreDialog::Name | KScoreDialog::Score | KScoreDialog::Level, this);
	dialog->initFromDifficulty(Kg::difficulty());
	dialog->exec();
	delete dialog;
}

void KapmanMainWindow::setSoundsEnabled(bool p_enabled) {
	m_game->setSoundsEnabled(p_enabled);
}

void KapmanMainWindow::showSettings() {
	if (KConfigDialog::showDialog("settings")) {
		return;
	}
	KConfigDialog* settingsDialog = new KConfigDialog(this, "settings", Settings::self());
	settingsDialog->addPage(new KGameThemeSelector(settingsDialog, Settings::self(), KGameThemeSelector::NewStuffDisableDownload), i18n("Theme"), "kapman");
	settingsDialog->setFaceType(KConfigDialog::Plain); //only one page -> no page selection necessary
	connect(settingsDialog, SIGNAL(settingsChanged(QString)), this, SLOT(loadSettings()));
	settingsDialog->show();
}

void KapmanMainWindow::loadSettings() {
	((GameScene*)m_view->scene())->loadTheme();
}

void KapmanMainWindow::close() {
	bool gameRunning;		// True if the game is running (game timer is active), false otherwise
   
	gameRunning = m_game->getTimer()->isActive();
	// If the game is running
	if (gameRunning) {
		// Pause the game
		m_game->pause();
	}
	// Confirm before closing
	if(KMessageBox::warningYesNo(this, i18n("Are you sure you want to quit Kapman?"), i18nc("To quit Kapman", "Quit")) == KMessageBox::Yes) {
		KXmlGuiWindow::close();
	}
	else {
		// If the game was running
		if (gameRunning) {
			// Resume the game
			m_game->start();
		}
	}
}

void KapmanMainWindow::displayLevel(unsigned int p_level)
{
	m_statusBar->changeItem(i18nc(
			"Used to display the current level of play to the user",
			"Level: %1", p_level), 1);
}

void KapmanMainWindow::displayScore(unsigned int p_score)
{
	m_statusBar->changeItem(i18nc(
			"Used to inform the user of their current score", "Score: %1",
			p_score), 2);
}

void KapmanMainWindow::displayLives(unsigned int p_lives)
{
	m_statusBar->changeItem(i18nc(
			"Used to tell the user how many lives they have left", "Lives: %1",
			p_lives), 4);
}

void KapmanMainWindow::resetStatusBar()
{
	displayLevel(0);
	displayScore(0);
	displayLives(initLives);
}
