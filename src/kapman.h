/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KAPMAN_H
#define KAPMAN_H

#include "character.h"

/**
 * @brief This class represents the main character of the game.
 */
class Kapman : public Character
{

    Q_OBJECT

private:

    /** Max speed ratio, compared with the initial speed  */
    static const qreal MAX_SPEED_RATIO;

    /** Kapman asked speed */
    qreal m_askedXSpeed, m_askedYSpeed;

public:

    /**
     * Creates a new Kapman instance.
     * @param p_x the initial x-coordinate
     * @param p_y the initial y-coordinate
     * @param p_maze the Maze the Kapman is on
     */
    Kapman(qreal p_x, qreal p_y, Maze *p_maze);

    /**
     * Deletes the Kapman instance.
     */
    ~Kapman() override;

    /**
     * Initializes the Kapman.
     */
    void init();

    /**
     * Makes the Kapman ask to go up
     */
    void goUp() override;

    /**
     * Makes the Kapman ask to go down
     */
    void goDown() override;

    /**
     * Makes the Kapman ask to go to the right
     */
    void goRight() override;

    /**
     * Makes the Kapman ask to go to the left
     */
    void goLeft() override;

    /**
     * Updates the Kapman move
     */
    void updateMove() override;

    /**
     * @return the asked x speed value
     */
    qreal getAskedXSpeed() const;

    /**
     * @return the asked y speed value
     */
    qreal getAskedYSpeed() const;

    /**
     * Manages the points won
     * @param p_element reference to the element eaten
     */
    void winPoints(Element *p_element);

    /**
     * Implements the Character function
     */
    void die();

    /**
     * Emits a signal to Kapmanitem in order to manage collisions
     */
    void emitGameUpdated();

    /**
     * Initializes the Kapman speed from the Character speed.
     */
    void initSpeedInc() override;

private:

    /**
     * Updates the Kapman direction with the asked direction
     */
    void updateDirection();

    /**
     * @return the next cell the kapman will move on with its asked direction
     */
    Cell getAskedNextCell();

    /**
     * Stops moving the Kapman
     */
    void stopMoving();

Q_SIGNALS:

    /**
     * Emitted when the direction changed
     */
    void directionChanged();

    /**
     * Signals to the game that the kapman win points
     * @param p_element reference to the element eaten
     */
    void sWinPoints(Element *p_element);

    /**
     * Signals to Kapmanitem that the game has been updated
     */
    void gameUpdated();

    /**
     * Emitted when the kapman stops moving
     */
    void stopped();
};

#endif
