/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CELL_H
#define CELL_H

#include <QtGlobal>

class Element;

/**
 * @brief This class represents a Cell of the Maze.
 */
class Cell
{

public:

    /** The Cell side size */
    static const qreal SIZE;

    /** The Cell possible types */
    enum Type {
        WALL = 0,
        CORRIDOR = 1,
        GHOSTCAMP = 2
    };

private:

    /** The Cell type */
    Type m_type;

    /** A reference on the Element that is on the Cell */
    Element *m_element;

    /** Cost used in A* pathfinding algorithm : lower is the cost, closer to the target Cell is this Cell */
    int m_cost;

    /** Parent node used in A* pathfinding algorithm : the Cell which enables to go to this Cell */
    Cell *m_parent;

public:

    /**
     * Creates a new Cell instance.
     */
    Cell();

    /**
     * Deletes the Cell instance.
     */
    ~Cell();

    /**
     * Gets the Cell type.
     * @return the Cell type
     */
    Type getType() const;

    /**
     * Sets the Cell type.
     * @param p_type the new type to set
     */
    void setType(Type p_type);

    /**
     * Gets the Element that is on the Cell.
     * @return the Element that is on the Cell
     */
    Element *getElement() const;

    /**
     * Sets the Element that is on the Cell.
     * @param p_element the Element to set on the Cell
     */
    void setElement(Element *p_element);

    /**
     * Gets the Cell cost for A* pathfinding algorithm.
     * @return the Cell cost for A* pathfinding algorithm
     */
    int getCost() const;

    /**
     * Sets a cost for the Cell, for A* pathfinding algorithm.
     * @param p_cost the cost of the Cell for A* pathfinding algorithm
     */
    void setCost(const int p_cost);

    /**
     * Gets the parent Cell of this Cell for A* pathfinding algorithm.
     * @return the Cell parent for A* pathfinding algorithm
     */
    Cell *getParent() const;

    /**
     * Sets the parent Cell of this Cell for A* pathfinding algorithm.
     * @param p_parent the parent of the Cell for A* pathfinding algorithm
     */
    void setParent(Cell *p_parent);
};

#endif

