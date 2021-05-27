/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoit Besse <besse.pb@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GHOSTITEM_H
#define GHOSTITEM_H

#include "characteritem.h"
#include "ghost.h"

/**
 * @brief This class is the graphical representation of a Ghost.
 */
class GhostItem : public CharacterItem
{

    Q_OBJECT

public:

    /**
     * Creates a new GhostItem instance.
     * @param p_model the Ghost model
     */
    explicit GhostItem(Ghost *p_model);

    /**
     * Deletes the CharacterItem instance.
     */
    ~GhostItem() override;

    /**
     * Ensures the blink timers are correctly set
     */
    void updateBlinkTimersDuration();

public Q_SLOTS:

    /**
     * Updates the view coordinates.
     * @param p_x the new x-coordinate
     * @param p_y the new y-coordinate
     */
    void update(qreal p_x, qreal p_y) override;

    /**
     * Update the image function of the Ghost state.
     */
    void updateState();

    /**
     * Implements the CharacterItem method.
     */
    void blink() override;
};

#endif

