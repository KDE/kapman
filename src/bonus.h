/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
    SPDX-FileCopyrightText: 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Johann Hingue <yoan1703@hotmail.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef BONUS_H
#define BONUS_H

#include "element.h"

/**
 * @brief This class represents a Bonus for Kapman.
 */
class Bonus : public Element
{
    Q_OBJECT
public:

    /**
     * Creates a new Bonus instance.
     * @param p_x the initial x-coordinate
     * @param p_y the initial y-coordinate
     * @param p_maze a reference to the Maze the Bonus will be on
     * @param p_points the value of the Bonus
     */
    Bonus(qreal p_x, qreal p_y, Maze *p_maze, int p_points);

    /**
     * Deletes the Bonus instance.
     */
    ~Bonus() override;

    /**
     * Computes an action on a collision with the Kapman.
     * @param p_kapman the Kapman instance that collides with the Bonus
     */
    void doActionOnCollision(Kapman *p_kapman) override;

    /**
     * Sets the given value to the Bonus.
     * @param p_points the value of the Bonus
     */
    void setPoints(const int p_points);
};

#endif

