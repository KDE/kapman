/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
    SPDX-FileCopyrightText: 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ENERGIZER_H
#define ENERGIZER_H

#include "element.h"

/**
 * @brief This class represents an energizer enabling to eat Ghosts.
 */
class Energizer : public Element
{

    Q_OBJECT

public:

    /** The value of an Energyzer */
    static const int POINTS;

public:

    /**
     * Creates a new Energizer instance.
     * @param p_x the x-coordinate
     * @param p_y the y-coordinate
     * @param p_maze the Maze the Energyzer is on
     * @param p_imageId the path to the Energyzer image
     */
    Energizer(qreal p_x, qreal p_y, Maze *p_maze, const QString &p_imageId);

    /**
     * Deletes the Energizer instance.
     */
    ~Energizer() override;

    /**
     * Gets the type of the Energyzer.
     * @return the type of the Energyzer
     */
    QString getType();

    /**
     * Computes an action on a collision with the Kapman.
     * @param p_kapman the instance of Kapman which collides with the Energyzer
     */
    void doActionOnCollision(Kapman *p_kapman) override;
};

#endif

