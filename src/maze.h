/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAZE_H
#define MAZE_H

#include "cell.h"

#include <QObject>
#include <QList>
#include <QPoint>

/**
 * @brief This class represents the Maze of the game.
 */
class Maze : public QObject
{

    Q_OBJECT

private:

    /** The Cell coordinates where the Ghosts go back when they have been eaten */
    QPoint m_resurrectionCell;

    /** The number of rows of the Maze */
    int m_nbRows;

    /** The number of columns of the Maze */
    int m_nbColumns;

    /** The Maze Cells */
    Cell **m_cells;

    /** The initial number of Elements in the Maze (when the game has not started) */
    int m_totalNbElem;

    /** The number of remaining Elements in the Maze (when the game is running) */
    int m_nbElem;

public:

    /**
     * Creates a new Maze instance.
     */
    Maze();

    /**
     * Deletes the Maze instance.
     */
    ~Maze() override;

    /**
     * Creates the Maze matrix.
     * @param p_nbRows the number of rows
     * @param p_nbColumns the number of columns
     */
    void init(const int p_nbRows, const int p_nbColumns);

    /**
     * Sets the CellType of the Cell whose coordinates are given in parameters.
     * @param p_row the Cell row
     * @param p_column the Cell column
     * @param p_type the Cell type
     */
    void setCellType(const int p_row, const int p_column, const Cell::Type p_type);

    /**
     * Sets the Element that is on the Cell whose coordinates are given in parameters.
     * @param p_row the Cell row
     * @param p_column the Cell column
     * @param p_element the Element that is on the Cell
     */
    void setCellElement(const int p_row, const int p_column, Element *p_element);

    /**
     * Sets the cell on witch the ghosts resurrect from prey state
     * @param p_resurrectionCell the cell on witch the ghosts resurrect
     */
    void setResurrectionCell(QPoint p_resurrectionCell);

    /**
     * Decrements the number of remaining Elements.
     */
    void decrementNbElem();

    /**
     * Resets the number of remaining Elements to the initial number.
     */
    void resetNbElem();

    /**
     * Gets the path, as a list of Cell coordinates, to go to the Ghost camp from the Cell whose coordinates are given in parameters.
     * This algorithm has been made from the A* algorithm.
     * @param p_row the row index of the starting Cell
     * @param p_column the column index of the starting Cell
     * @return a list of Cell coordinates to go to the Ghost camp
     */
    QList<QPoint> getPathToGhostCamp(const int p_row, const int p_column) const;

    /**
     * Gets the Cell at the given coordinates.
     * @param p_row the row index
     * @param p_column the column index
     * @return the Cell at the given row and column
     */
    Cell getCell(const int p_row, const int p_column) const;

    /**
     * Gets the coordinates of the given Cell as a QPoint.
     * @param p_cell the searched Cell
     * @return the row and column of the given Cell
     */
    QPoint getCoords(Cell *p_cell) const;

    /**
     * Gets the row index corresponding to the given y-coordinate.
     * @param p_y the y-coordinate to convert into row index
     * @return the row index corresponding to the given y-coordinate
     */
    int getRowFromY(const qreal p_y) const;

    /**
     * Gets the column index corresponding to the given x-coordinate.
     * @param p_x the x-coordinate to convert into column index
     * @return the column index corresponding to the given x-coordinate
     */
    int getColFromX(const qreal p_x) const;

    /**
     * Gets the number of columns of the Maze.
     * @return the number of columns
     */
    int getNbColumns() const;

    /**
     * Gets the number of rows of the Maze.
     * @return the number of rows
     */
    int getNbRows() const;

    /**
     * Gets the number of remaining Elements still on the Maze.
     * @return the number of remaining Elements
     */
    int getNbElem() const;

    /**
     * Gets the number of Elements initially on the Maze.
     * @return the initial number of Elements
     */
    int getTotalNbElem() const;

    /**
     * Gets the cell on witch the ghosts resurrects
     * @return the cell on witch the ghosts resurrects
     */
    QPoint getResurrectionCell() const;

Q_SIGNALS:

    /**
     * Emitted when all the elements on the Maze have been eaten.
     */
    void allElementsEaten();
};

#endif

