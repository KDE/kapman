/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
    SPDX-FileCopyrightText: 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef PILL_H
#define PILL_H

#include "element.h"

/**
 * @brief This class represents a Pill enabling to earn points.
 */
class Pill : public Element
{
    Q_OBJECT
public:

    /** The Pill value */
    static const int POINTS;

public:

    /**
     * Creates a new Pill instance.
     */
    Pill(qreal p_x, qreal p_y, Maze *p_maze, const QString &p_imageId);

    /**
     * Deletes the Pill instance.
     */
    ~Pill() override;

    /**
     * Computes an action on a collision with the Kapman.
     * @param p_kapman the instance of Kapman which collides with the Pill
     */
    void doActionOnCollision(Kapman *p_kapman) override;
};

#endif

