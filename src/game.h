/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "kapman.h"
#include "ghost.h"
#include "bonus.h"

#include <QPointF>
#include <QTimer>
#include <QKeyEvent>
#include <KgSound>

/**
 * @brief This class manages the game main loop : it regularly checks the key press events, computes the character moves and updates their coordinates.
 */
class Game : public QObject
{

    Q_OBJECT

public :
    /** Ratio which modify the timers function of the difficulty */
    static qreal s_durationRatio;

    /** Timer duration for prey state in medium difficulty */
    static int s_preyStateDuration;

    /** Timer duration for bonus apparition in medium difficulty */
    static int s_bonusDuration;

private :

    /** Number of FPS */
    static const int FPS;

    /** The game different states : RUNNING, PAUSED_LOCKED, PAUSED_UNLOCKED */
    enum State {
        RUNNING,            // Game running
        PAUSED_LOCKED,      // Game paused and user is not allowed to unpause
        PAUSED_UNLOCKED     // Game paused and user is allowed to unpause
    };
    /** A flag for the State enum */
    Q_DECLARE_FLAGS(GameStates, State)

    /** The game state */
    State m_state;

    /** The Game main timer */
    QTimer *m_timer;

    /** The Bonus timer to make it disappear if it is not eaten after a given time */
    QTimer *m_bonusTimer;

    /** Timer to manage the prey state of the ghosts */
    QTimer *m_preyTimer;

    /** The Maze */
    Maze *m_maze;

    /** The main Character */
    Kapman *m_kapman;

    /** The Ghosts */
    QList<Ghost *> m_ghosts;

    /** The Bonus instance */
    Bonus *m_bonus;

    /** A flag to know if the player has cheated during the game */
    bool m_isCheater;

    /** The remaining number of lives */
    int m_lives;

    /** The won points */
    long m_points;

    /** The current game level */
    int m_level;

    /** The number of eaten ghosts since the beginning of the current level */
    int m_nbEatenGhosts;

    /** Flag if sound is enabled */
    bool m_soundEnabled;

    KgSound m_soundGameOver;
    KgSound m_soundGhost;
    KgSound m_soundGainLife;
    KgSound m_soundEnergizer;
    KgSound m_soundBonus;
    KgSound m_soundPill;
    KgSound m_soundLevelUp;

public:

    /**
     * Creates a new Game instance.
     */
    Game();

    /**
     * Deletes the Game instance.
     */
    ~Game() override;

    /**
     * Starts the Game.
     */
    void start();

    /**
     * Pauses the Game.
     * @param p_locked if true the player will be unable to unset the pause.
     */
    void pause(bool p_locked = false);

    /**
     * Pauses / unpauses the game.
     * @param p_locked if true the player will be unable to unset the pause.
     */
    void switchPause(bool p_locked = false);

    /**
     * @return the Maze instance
     */
    Maze *getMaze() const;

    /**
     * @return the Kapman model
     */
    Kapman *getKapman() const;

    /**
     * @return the Ghost models
     */
    QList<Ghost *> getGhosts() const;

    /**
     * @return the Bonus instance
     */
    Bonus *getBonus() const;

    /**
     * @return the main timer
     */
    QTimer *getTimer() const;

    /**
     * @return true if the Game is paused, false otherwise
     */
    bool isPaused() const;

    /**
     * @return true if the player has cheated during the game, false otherwise
     */
    bool isCheater() const;

    /**
     * @return the score
     */
    int getScore() const;

    /**
     * @return the number of remaining lives
     */
    int getLives() const;

    /**
     * @return the current level
     */
    int getLevel() const;

    /**
     * Sets the level to the given number.
     * @param p_level the new level
     */
    void setLevel(int p_level);

    /**
     * Create the new Bonus
     * @param p_position the Bonus position
     */
    void createBonus(QPointF p_position);

    /**
     * Create the new Kapman
     * @param p_position the Kapman position
     */
    void createKapman(QPointF p_position);

    /**
     * Create the new Ghost
     * @param p_position the Ghost position
     * @param p_imageId the image of the Ghost
     */
    void createGhost(QPointF p_position, const QString &p_imageId);

    /**
     * Initializes a Maze
     * @param p_nbRows the number of rows
     * @param p_nbColumns the number of columns
     */
    void initMaze(const int p_nbRows, const int p_nbColumns);

    /**
     * Enables / disables the sounds.
     * @param p_enabled if true the sounds will be enabled, otherwise they will be disabled
     */
    void setSoundsEnabled(bool p_enabled);

private:

    /**
     * Initializes the character coordinates.
     */
    void initCharactersPosition();

    /**
     * Calculates and update the ghosts speed depending on the ghosts speed
     * The value is in Ghost::s_speed
     */
    void setTimersDuration();
    void setPreyTimerDuration();
    void setBonusTimerDuration();

public Q_SLOTS:

    /**
     * Manages the key press events.
     * @param p_event the key press event
     */
    void keyPressEvent(QKeyEvent *p_event);

    /**
     * Resumes the Game after the Kapman death.
     */
    void resumeAfterKapmanDeath();

private Q_SLOTS:

    /**
     * Updates the Game data.
     */
    void update();

    /**
     * Manages the loss of a life.
     */
    void kapmanDeath();

    /**
     * Manages the death of a Ghost.
     */
    void ghostDeath(Ghost *p_ghost);

    /**
     * Increases the score considering the eaten Element.
     * @param p_element the eaten Element
     */
    void winPoints(Element *p_element);

    /**
     * Starts the next level.
     */
    void nextLevel();

    /**
     * Hides the Bonus.
     */
    void hideBonus();

    /**
     * Ends the Ghosts prey state.
     */
    void endPreyState();

Q_SIGNALS:

    /**
     * Emitted when the Game is started.
     */
    void gameStarted();

    /**
     * Emitted when the Game is over.
     */
    void gameOver();

    /**
     * Emitted when a level begins, if level up or if a life has been lost.
     * @param p_newLevel true if a new level is beginning, false otherwise
     */
    void levelStarted(const bool p_newLevel);

    /**
     * Emitted when the pause state has changed.
     * @param p_pause true if the Game is paused, false otherwise
     * @param p_fromUser true if the Game has been paused due to an action the player has done, false otherwise
     */
    void pauseChanged(const bool p_pause, const bool p_fromUser);

    /**
     * Emitted when an Element has been eaten.
     * @param p_x the Element x-coordinate
     * @param p_y the Element y-coordinate
     */
    void elementEaten(const qreal p_x, const qreal p_y);

    /**
     * Emitted when the Bonus has to be displayed.
     */
    void bonusOn();

    /**
     * Emitted when the Bonus has to disappear.
     */
    void bonusOff();

    /**
     * Emitted when the level have changed.
     * @param p_level the new level data
     */
    void levelChanged(unsigned int p_level);

    /**
     * Emitted when the score have changed.
     * @param p_score the new score data
     */
    void scoreChanged(unsigned int p_score);

    /**
     * Emitted when the lives have changed.
     * @param p_lives the new lives data
     */
    void livesChanged(unsigned int p_lives);

    /**
     * Emitted when a ghost or a bonus is eaten. It tells to the scene to
     * display the number of won points
     * @param p_wonPoints the value to display
     * @param p_xPos the x position of the label
     * @param p_yPos the y position of the label
     */
    void pointsToDisplay(long p_wonPoints, qreal p_xPos, qreal p_yPos);
};

#endif

