/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoit Bessse <besse@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kapmanmainwindow.h"
#include "gamescene.h"
#include "settings.h"
// KDEGames
#include <KGameDifficulty>
#include <KGameHighScoreDialog>
#include <KGameStandardAction>
#include <KGameThemeProvider>
#include <KGameThemeSelector>
// KF
#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
#include <KStandardGuiItem>
#include <KToggleAction>
#include <KToggleFullScreenAction>
// Qt
#include <QAction>
#include <QInputDialog>
#include <QLabel>
#include <QMenuBar>
#include <QPointer>
#include <QStatusBar>

KapmanMainWindow::KapmanMainWindow()
{
    m_themeProvider = new KGameThemeProvider(QByteArray(), this); // empty config key to disable internal config
    m_themeProvider->discoverThemes(QStringLiteral("themes"), // theme data location
                                    QStringLiteral("default")); // default theme name

    const QByteArray themeIdentifier = Settings::theme().toUtf8();
    const QList<const KGameTheme *> themes = m_themeProvider->themes();
    for (auto *theme : themes) {
        if (theme->identifier() == themeIdentifier) {
            m_themeProvider->setCurrentTheme(theme);
            break;
        }
    }
    connect(m_themeProvider, &KGameThemeProvider::currentThemeChanged, this, &KapmanMainWindow::onThemeChanged);

    m_themeSelector = new KGameThemeSelector(m_themeProvider);

    // Initialize the game
    m_game = nullptr;
    m_view = nullptr;
    // Set the window menus
    KGameStandardAction::gameNew(this, &KapmanMainWindow::newGame, actionCollection());
    KGameStandardAction::highscores(this, &KapmanMainWindow::showHighscores, actionCollection());
    KStandardAction::preferences(this, &KapmanMainWindow::showSettings, actionCollection());

    KStandardAction::fullScreen(this, &KapmanMainWindow::viewFullScreen, this, actionCollection());

    KGameStandardAction::quit(this, &KapmanMainWindow::close, actionCollection());
    auto soundAction = new KToggleAction(QIcon::fromTheme(QStringLiteral("speaker")), i18nc("@option:check", "Play Sounds"), this);
    soundAction->setChecked(Settings::sounds());
    actionCollection()->addAction(QStringLiteral("sounds"), soundAction);
    connect(soundAction, &KToggleAction::triggered, this, &KapmanMainWindow::setSoundsEnabled);
    auto levelAction = new QAction(i18nc("@action", "&Change Level…"), this);
    actionCollection()->addAction(QStringLiteral("level"), levelAction);
    connect(levelAction, &QAction::triggered, this, &KapmanMainWindow::changeLevel);
    // Add a statusbar to show level,score,lives information
    m_statusBar = statusBar();
    mLevel = new QLabel(i18nc("Used to display the current level of play to the user", "Level: %1", 1));
    m_statusBar->addPermanentWidget(mLevel);
    mScore = new QLabel(i18nc("Used to inform the user of their current score", "Score: %1", 0));
    m_statusBar->addPermanentWidget(mScore);
    mLives = new QLabel(i18nc("Used to tell the user how many lives they have left", "Lives: %1", initLives));
    m_statusBar->addPermanentWidget(mLives);

    // Initialize the KGameDifficulty singleton
    KGameDifficulty::global()->addStandardLevelRange(KGameDifficultyLevel::Easy,
                                                     KGameDifficultyLevel::Hard, // range
                                                     KGameDifficultyLevel::Medium // default
    );
    KGameDifficultyGUI::init(this);
    connect(KGameDifficulty::global(), &KGameDifficulty::currentLevelChanged, this, &KapmanMainWindow::initGame);
    // Set up the window
    setupGUI();

    menuBar()->setVisible(!isFullScreen());
    statusBar()->setVisible(!isFullScreen());

    initGame();
}

KapmanMainWindow::~KapmanMainWindow()
{
    delete m_themeSelector;
    delete m_statusBar;
    delete m_game;
    delete m_view;
}

void KapmanMainWindow::initGame()
{
    // Create a new Game instance
    delete m_game;
    m_game = new Game();
    connect(m_game, &Game::gameOver, this, &KapmanMainWindow::handleGameOver);
    connect(m_game, &Game::levelChanged, this, &KapmanMainWindow::displayLevel);
    connect(m_game, &Game::scoreChanged, this, &KapmanMainWindow::displayScore);
    connect(m_game, &Game::livesChanged, this, &KapmanMainWindow::displayLives);

    // Create a new GameView instance
    delete m_view;
    m_view = new GameView(m_game, m_themeProvider->currentTheme());
    m_view->setBackgroundBrush(Qt::black);
    setCentralWidget(m_view);
    m_view->setFocus();
    // For some reason, calling setFocus() immediately won't work after the
    // score dialog has been shown, so do it again after an eventloop run.
    QTimer::singleShot(0, m_view, qOverload<>(&QWidget::setFocus));
    resetStatusBar();
}

void KapmanMainWindow::newGame()
{
    bool gameRunning; // True if the game is running (game timer is active), false otherwise

    gameRunning = m_game->getTimer()->isActive();
    // If the game is running
    if (gameRunning) {
        // Pause the game
        m_game->pause();
    }

    // Confirm before starting a new game
    if (KMessageBox::warningTwoActions(this,
                                       i18n("Are you sure you want to quit the current game?"),
                                       i18nc("@title:window", "New Game"),
                                       KGuiItem(i18nc("@action;button", "Quit Game"), QStringLiteral("window-close")),
                                       KStandardGuiItem::cancel())
        == KMessageBox::PrimaryAction) {
        // Start a new game
        initGame();
    } else {
        // If the game was running
        if (gameRunning) {
            // Resume the game
            m_game->start();
        }
    }
}

void KapmanMainWindow::handleGameOver()
{
    bool gameRunning; // True if the game is running (game timer is active), false otherwise

    gameRunning = m_game->getTimer()->isActive();
    // If the game is running
    if (gameRunning) {
        // Pause the game
        m_game->pause();
    }
    // Display the score information
    KMessageBox::information(this, i18np("Your score is %1 point.", "Your score is %1 points.", m_game->getScore()), i18n("Game Over"));
    // manage Highscores only if player did not cheat
    if (m_game->isCheater()) {
        KMessageBox::information(this, i18n("You cheated, no Highscore for you ;)"), i18n("Cheater!"));
    } else {
        // Add the score to the highscores table
        QPointer<KGameHighScoreDialog> dialog =
            new KGameHighScoreDialog(KGameHighScoreDialog::Name | KGameHighScoreDialog::Score | KGameHighScoreDialog::Level, this);
        dialog->initFromDifficulty(KGameDifficulty::global());
        KGameHighScoreDialog::FieldInfo scoreInfo;
        scoreInfo[KGameHighScoreDialog::Level].setNum(m_game->getLevel());
        scoreInfo[KGameHighScoreDialog::Score].setNum(m_game->getScore());
        // If the new score is a highscore then display the highscore dialog
        if (dialog->addScore(scoreInfo)) {
            dialog->exec();
        }
        delete dialog;
    }
    // Start a new game
    initGame();
}

void KapmanMainWindow::changeLevel()
{
    const int newLevel = QInputDialog::getInt(this,
                                              i18nc("@title:window", "Change Level"),
                                              i18nc("@label:textbox The number of the game level", "Level:"),
                                              m_game->getLevel(),
                                              1,
                                              1000000,
                                              1);
    if (newLevel > 0) {
        m_game->setLevel(newLevel);
    }
}

void KapmanMainWindow::showHighscores()
{
    QPointer<KGameHighScoreDialog> dialog =
        new KGameHighScoreDialog(KGameHighScoreDialog::Name | KGameHighScoreDialog::Score | KGameHighScoreDialog::Level, this);
    dialog->initFromDifficulty(KGameDifficulty::global());
    dialog->exec();
    delete dialog;
}

void KapmanMainWindow::setSoundsEnabled(bool p_enabled)
{
    m_game->setSoundsEnabled(p_enabled);
}

void KapmanMainWindow::showSettings()
{
    m_themeSelector->showAsDialog();
}

void KapmanMainWindow::onThemeChanged(const KGameTheme *theme)
{
    // sync to settings store
    Settings::setTheme(QString::fromUtf8(theme->identifier()));
    Settings::self()->save();
    // trigger update of resources, then display
    ((GameScene *)m_view->scene())->loadTheme(theme);
}

void KapmanMainWindow::close()
{
    bool gameRunning; // True if the game is running (game timer is active), false otherwise

    gameRunning = m_game->getTimer()->isActive();
    // If the game is running
    if (gameRunning) {
        // Pause the game
        m_game->pause();
    }
    // Confirm before closing
    if (KMessageBox::warningTwoActions(this,
                                       i18n("Are you sure you want to quit Kapman?"),
                                       i18nc("@title:window To quit Kapman", "Quit"),
                                       KStandardGuiItem::quit(),
                                       KStandardGuiItem::cancel())
        == KMessageBox::PrimaryAction) {
        KXmlGuiWindow::close();
    } else {
        // If the game was running
        if (gameRunning) {
            // Resume the game
            m_game->start();
        }
    }
}

void KapmanMainWindow::displayLevel(unsigned int p_level)
{
    mLevel->setText(i18nc("Used to display the current level of play to the user", "Level: %1", p_level));
}

void KapmanMainWindow::displayScore(unsigned int p_score)
{
    mScore->setText(i18nc("Used to inform the user of their current score", "Score: %1", p_score));
}

void KapmanMainWindow::displayLives(unsigned int p_lives)
{
    mLives->setText(i18nc("Used to tell the user how many lives they have left", "Lives: %1", p_lives));
}

void KapmanMainWindow::resetStatusBar()
{
    displayLevel(1);
    displayScore(0);
    displayLives(initLives);
}

void KapmanMainWindow::viewFullScreen(bool fullScreen)
{
    KToggleFullScreenAction::setFullScreen(this, fullScreen);

    menuBar()->setVisible(!fullScreen);
    statusBar()->setVisible(!fullScreen);
}

#include "moc_kapmanmainwindow.cpp"
