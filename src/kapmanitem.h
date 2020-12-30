/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KAPMANITEM_H
#define KAPMANITEM_H

#include "characteritem.h"
#include "kapman.h"

#include <QTimeLine>

/**
 * @brief This class manage the display of the Kapman.
 */
class KapmanItem : public CharacterItem
{

    Q_OBJECT

private:

    /** Number of frames to animate the KapmanItem */
    static const int NB_FRAMES;

    /** Animation update interval */
    static const int ANIM_LOW_SPEED;
    static const int ANIM_MEDIUM_SPEED;
    static const int ANIM_HIGH_SPEED;

    /** Timer used to animate the KapmanItem */
    QTimeLine *m_animationTimer;

    /** Rotation flag set by theme */
    bool m_rotationFlag;

public:

    /**
     * Creates a new KapmanItem instance.
     * @param p_model the Kapman model
     */
    explicit KapmanItem(Kapman *p_model);

    /**
     * Deletes the KapmanItem instance.
     */
    ~KapmanItem() override;

public Q_SLOTS:

    /**
     * Rotates the image function of the Kapman direction.
     */
    void updateDirection();

    /**
     * Manages the collisions with any Element.
     */
    void manageCollision();

    /**
     * Updates the KapmanItem coordinates.
     * @param p_x the new x-coordinate
     * @param p_y the new y-coordinate
     */
    void update(qreal p_x, qreal p_y) override;

    /**
     * Starts the KapmanItem animation.
     */
    void startAnim();

    /**
     * Pauses the KapmanItem animation.
     */
    void pauseAnim();

    /**
     * Resumes the KapmanItem animation.
     */
    void resumeAnim();

    /**
     * Stops the KapmanItem animation.
     */
    void stopAnim();

    /**
     * Sets the given frame to the KapmanItem.
     * @param p_frame the frame to set
     */
    void setFrame(const int p_frame);

    /**
     * Implements the CharacterItem method.
     */
    void startBlinking() override;

    /**
     * Implements the CharacterItem method.
     */
    void blink() override;

    /**
     * Set if the KapmanItem should be rotated (set by theme flag RotateKapman).
     * @param rotate 0 or 1
     */
    void setRotationFlag(bool rotate)
    {
        m_rotationFlag = rotate;
    }

};

#endif

