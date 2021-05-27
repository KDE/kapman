/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GHOST_H
#define GHOST_H

#include "character.h"
#include "kapman.h"

/**
 * @brief This class represents a Ghost for kapman.
 */
class Ghost : public Character
{

    Q_OBJECT

public:

    /** The ghost possible states */
    enum State {
        HUNTER = 0,
        PREY = 1,
        EATEN = 2
    };

    /** The value of an Ghost */
    static const int POINTS;

private:

    /** Max speed ratio, compared with the initial speed  */
    static const qreal MAX_SPEED_RATIO;

    /** The path to the Ghost image */
    QString m_imageId;

    /** The ghost current state */
    State m_state;

    /** A list of Cells to go to the camp from the current cell */
    QList<QPoint> m_pathToCamp;

    bool m_preyStateAlmostOver;

public:

    /**
     * Creates a new Ghost instance.
     * @param p_x the initial x-coordinate
     * @param p_y the initial y-coordinate
     * @param p_imageId path to the image of the related item
     * @param p_maze the Maze the Ghost is on
     */
    Ghost(qreal p_x, qreal p_y, const QString &p_imageId, Maze *p_maze);

    /**
     * Deletes the Ghost instance.
     */
    ~Ghost() override;

    /**
     * Updates the Ghost move.
     */
    void updateMove() override;

    /**
     * Updates the Ghost with a direction to follow.
     * @param p_row x coordinate of the cell to reach
     * @param p_col y coordinate of the cell to reach
     */
    void updateMove(int p_row, int p_col);

    /**
     * Gets the path to the Ghost image.
     * @return the path to the Ghost image
     */
    QString getImageId() const;

    /**
     * Gets the current state of the Ghost.
     * @return the Ghost state
     */
    State getState() const;

    /**
     * Sets the Ghost state to the given value.
     * @param p_state the new Ghost state
     */
    void setState(Ghost::State p_state);

    /**
     * Manages the collision with the Kapman.
     * @param p_kapman the instance of Kapman which collides with the Ghost
     */
    void doActionOnCollision(Kapman *p_kapman) override;

    /**
     * Initializes the Ghost speed from the Character speed.
     */
    void initSpeedInc() override;

    void setPreyStateAlmostOverEnabled(bool enable);
    bool preyStateAlmostOver() const;
private:

    /**
     * Makes the Ghost go up.
     */
    void goUp() override;

    /**
     * Makes the Ghost go down.
     */
    void goDown() override;

    /**
     * Makes the Ghost go to the right.
     */
    void goRight() override;

    /**
     * Makes the Ghost go to the left.
     */
    void goLeft() override;

Q_SIGNALS:

    /**
     * Emitted when the Kapman has lost a life.
     */
    void lifeLost();

    /**
     * Emitted when the Ghost has been eaten.
     * @param p_ghost the eaten Ghost (this)
     */
    void ghostEaten(Ghost *p_ghost);

    /**
     * Emitted when the Ghost has changed his state.
     */
    void stateChanged();
};

#endif

