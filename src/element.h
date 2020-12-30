/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>

#include "maze.h"

class Kapman;

/**
 * @brief This class describes the common characteristics and behaviour of any game Element (character or item).
 */
class Element : public QObject
{

    Q_OBJECT

public:

    /** The Element possible types */
    enum Type {
        KAPMAN = 0,
        GHOST = 1,
        PILL = 2,
        ENERGYZER = 3,
        BONUS = 4
    };

protected:

    /** The Element type */
    Type m_type;

    /** The Element initial x-coordinate */
    qreal m_xInit;

    /** The Element initial y-coordinate */
    qreal m_yInit;

    /** The Element current x-coordinate */
    qreal m_x;

    /** The Element current y-coordinate */
    qreal m_y;

    /** The Maze the Element is on */
    Maze *m_maze;

    /** The Id of the Element */
    QString m_imageId;

    /** Points won when the Element is eaten */
    int m_points;

public:

    /**
     * Creates a new Element instance.
     * @param p_x the initial x-coordinate
     * @param p_y the initial y-coordinate
     * @param p_maze the Maze the Element is on
     */
    Element(qreal p_x, qreal p_y, Maze *p_maze);

    /**
     * Deletes the Element instance.
     */
    ~Element() override;

    /**
     * Computes an action on a collision with the Kapman.
     * @param p_kapman the instance of Kapman which collides with the Element
     */
    virtual void doActionOnCollision(Kapman *p_kapman);

    /**
     * Gets the path to the Element image.
     * @return the path to the Element image
     */
    QString getImageId() const;

    /**
     * Gets the value of the Element.
     * @return the points won when the Element is eaten
     */
    int getPoints() const;

    /**
     * Gets the type of the Element.
     * @return the Element type
     */
    Element::Type getType() const;

    /**
     * Sets the Element image.
     * @param p_imageId the image to set
     */
    void setImageId(const QString &p_imageId);

    /**
     * Gets the Element x-coordinate.
     * @return the x-coordinate
     */
    qreal getX() const;

    /**
     * Gets the Element y-coordinate.
     * @return the y-coordinate
     */
    qreal getY() const;

    /**
     * Sets the Element x-coordinate to the given value
     * @param p_x the x-coordinate to set
     */
    void setX(qreal p_x);

    /**
     * Sets the Element y-coordinate to the given value
     * @param p_y the y-coordinate to set
     */
    void setY(qreal p_y);

    /**
    * Initializes Element x-coordinate and y-coordinate with
    * initial values
    */
    void initCoordinate();

Q_SIGNALS:

    /**
     * Emitted on Element move.
     * @param p_x the new x-coordinate
     * @param p_y the new y-coordinate
     */
    void moved(qreal p_x, qreal p_y);
};

#endif

