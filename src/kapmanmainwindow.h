/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoit Bessse <besse@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KAPMANMAINWINDOW_H
#define KAPMANMAINWINDOW_H

#include "game.h"
#include "gameview.h"

#include <KXmlGuiWindow>
#include <QGraphicsView>

static const int initLives = 3;

class QStatusBar;
class QLabel;

/**
 * @brief This class enables to create the main window for Kapman.
 */
class KapmanMainWindow : public KXmlGuiWindow
{

    Q_OBJECT

private :

    /** The GameView instance that manages the game drawing and the collisions */
    GameView *m_view = nullptr;

    /** The Game instance that manages the main loop and events */
    Game *m_game = nullptr;

    QStatusBar *m_statusBar = nullptr;
    QLabel *mLevel = nullptr;
    QLabel *mScore = nullptr;
    QLabel *mLives = nullptr;

public:

    /**
     * Creates a new KapmanMainWindow instance.
     */
    KapmanMainWindow();

    /**
     * Deletes the KapmanMainWindow instance.
     */
    ~KapmanMainWindow() override;

private Q_SLOTS:

    /**
     * Initializes the KapmanMainWindow for a new game.
     * Creates a new Game instance and a new GameView instance that displays the game.
     */
    void initGame();

    void handleGameOver();

    /**
     * Starts a new game.
     */
    void newGame();

    /**
     * Shows the highscores dialog.
     */
    void showHighscores();

    /**
     * Shows a dialog enabling to change the current level.
     */
    void changeLevel();

    /**
     * Sets the sounds enabled / disabled.
     * @param p_enabled if true the sounds will be enabled, otherwise they will be disabled
     */
    void setSoundsEnabled(bool p_enabled);

    /**
     * Shows the settings dialog.
     */
    void showSettings();

    /**
     * Loads the settings.
     */
    void loadSettings();

    /**
     * Closes the KapmanMainWindow.
     */
    void close();

    /**
     * Refreshes new level value on Status Bar.
     * @param p_level is level value
     */
    void displayLevel(unsigned int p_level);

    /**
     * Refreshes new score value on Status Bar.
     * @param p_score is score value
     */
    void displayScore(unsigned int p_score);

    /**
     * Refreshes new lives value on Status Bar.
     * @param p_lives is lives value
     */
    void displayLives(unsigned int p_lives);

    /**
     * Resets the status bar values altogether for convenience.
     */
    void resetStatusBar();
};

#endif

