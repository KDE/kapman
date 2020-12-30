/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "maze.h"

#include <math.h>
#include <QDebug>

Maze::Maze() : m_totalNbElem(0), m_nbElem(0)
{

}

Maze::~Maze()
{
    for (int i = 0 ; i < m_nbRows; ++i) {
        delete[] m_cells[i];
    }
    delete[] m_cells;
}

void Maze::init(const int p_nbRows, const int p_nbColumns)
{
    m_nbRows = p_nbRows;
    m_nbColumns = p_nbColumns;
    m_cells = new Cell*[m_nbRows];
    for (int i = 0; i < m_nbRows; ++i) {
        m_cells[i] = new Cell[m_nbColumns];
    }
}

void Maze::setCellType(const int p_row, const int p_column, const Cell::Type p_type)
{
    if (p_row < 0 || p_row >= m_nbRows || p_column < 0 || p_column >= m_nbColumns) {
        qCritical() << "Bad maze coordinates";
    }
    m_cells[p_row][p_column].setType(p_type);
}

void Maze::setCellElement(const int p_row, const int p_column, Element *p_element)
{
    if (p_row < 0 || p_row >= m_nbRows || p_column < 0 || p_column >= m_nbColumns) {
        qCritical() << "Bad maze coordinates";
    }
    m_cells[p_row][p_column].setElement(p_element);
    if (p_element != nullptr) {
        m_totalNbElem++;
        m_nbElem++;
    }
}

void Maze::setResurrectionCell(QPoint p_resurrectionCell)
{
    // TODO : COORDINATES INVERTED, NEED TO CORRECT IT in the findPAth algorithm
    m_resurrectionCell.setX(p_resurrectionCell.y());
    m_resurrectionCell.setY(p_resurrectionCell.x());
}

void Maze::decrementNbElem()
{
    m_nbElem--;
    if (m_nbElem == 0) {
        Q_EMIT allElementsEaten();
    }
}

void Maze::resetNbElem()
{
    m_nbElem = m_totalNbElem;
}

QList<QPoint> Maze::getPathToGhostCamp(const int p_row, const int p_column) const
{
    QList<QPoint> path;
    QList<QPoint> openList;
    QList<QPoint> closedList;
    QPoint currentCell;
    QPoint tmpCell;
    int lowestCost;
    int icurrent = 0;
    int oldSize = 0;

    // Initialize the starting cell
    m_cells[p_row][p_column].setCost(abs(m_resurrectionCell.y() - p_row) + abs(m_resurrectionCell.x() - p_column));
    // Add the starting cell to the openList
    openList.append(QPoint(p_column, p_row));
    // While the closed list does not contain the target cell
    while (!closedList.contains(QPoint(m_resurrectionCell.x(), m_resurrectionCell.y())) && openList.size() != oldSize) {
        // Look for the lowest cost cell on the open list
        lowestCost = 1000;
        for (int i = 0; i < openList.size(); ++i) {
            if (m_cells[openList[i].y()][openList[i].x()].getCost() < lowestCost) {
                lowestCost = m_cells[openList[i].y()][openList[i].x()].getCost();
                currentCell = openList[i];
                icurrent = i;
            }
        }
        // Switch this cell to the closed list
        closedList.append(currentCell);
        openList.removeAt(icurrent);
        oldSize = openList.size();
        // For each of the 4 cells adjacent to the current node
        // Left
        tmpCell.setX(currentCell.x() - 1);
        tmpCell.setY(currentCell.y());
        if (m_cells[tmpCell.y()][tmpCell.x()].getType() != Cell::WALL) {
            // If the cell is not in the closed list or the open list
            if (!closedList.contains(tmpCell) && !openList.contains(tmpCell)) {
                // Initialize the cell
                m_cells[tmpCell.y()][tmpCell.x()].setCost(
                    abs(m_resurrectionCell.y() - tmpCell.y()) + abs(m_resurrectionCell.x() - (tmpCell.x())));
                m_cells[tmpCell.y()][tmpCell.x()].setParent(&m_cells[currentCell.y()][currentCell.x()]);
                // Add it to the open list
                openList.append(tmpCell);
            }
        }
        // Right
        tmpCell.setX(currentCell.x() + 1);
        tmpCell.setY(currentCell.y());
        if (m_cells[tmpCell.y()][tmpCell.x()].getType() != Cell::WALL) {
            // If the cell is not in the closed list or the open list
            if (!closedList.contains(tmpCell) && !openList.contains(tmpCell)) {
                // Initialize the cell
                m_cells[tmpCell.y()][tmpCell.x()].setCost(
                    abs(m_resurrectionCell.y() - tmpCell.y()) + abs(m_resurrectionCell.x() - (tmpCell.x())));
                m_cells[tmpCell.y()][tmpCell.x()].setParent(&m_cells[currentCell.y()][currentCell.x()]);
                // Add it to the open list
                openList.append(tmpCell);
            }
        }
        // Top
        tmpCell.setX(currentCell.x());
        tmpCell.setY(currentCell.y() - 1);
        if (m_cells[tmpCell.y()][tmpCell.x()].getType() != Cell::WALL) {
            // If the cell is not in the closed list or the open list
            if (!closedList.contains(tmpCell) && !openList.contains(tmpCell)) {
                // Initialize the cell
                m_cells[tmpCell.y()][tmpCell.x()].setCost(
                    abs(m_resurrectionCell.y() - tmpCell.y()) + abs(m_resurrectionCell.x() - (tmpCell.x())));
                m_cells[tmpCell.y()][tmpCell.x()].setParent(&m_cells[currentCell.y()][currentCell.x()]);
                // Add it to the open list
                openList.append(tmpCell);
            }
        }
        // Bottom
        tmpCell.setX(currentCell.x());
        tmpCell.setY(currentCell.y() + 1);
        if (m_cells[tmpCell.y()][tmpCell.x()].getType() != Cell::WALL) {
            // If the cell is not in the closed list or the open list
            if (!closedList.contains(tmpCell) && !openList.contains(tmpCell)) {
                // Initialize the cell
                m_cells[tmpCell.y()][tmpCell.x()].setCost(
                    abs(m_resurrectionCell.y() - tmpCell.y()) + abs(m_resurrectionCell.x() - (tmpCell.x())));
                m_cells[tmpCell.y()][tmpCell.x()].setParent(&m_cells[currentCell.y()][currentCell.x()]);
                // Add it to the open list
                openList.append(tmpCell);
            }
        }
    }
    if (oldSize == openList.size()) {
        qCritical() << "Path to ghost home not found";
        return QList<QPoint>();
    }
    // Save the path : from the target cell, go from each cell to its parent cell until reaching the starting cell
    for (Cell *cell = &m_cells[m_resurrectionCell.y()][m_resurrectionCell.x()];
            cell->getParent() != &m_cells[p_row][p_column]; cell = cell->getParent()) {
        path.prepend(getCoords(cell));
    }

    return path;
}

Cell Maze::getCell(const int p_row, const int p_column) const
{
    if (p_row < 0 || p_row >= m_nbRows ||
            p_column < 0 || p_column >= m_nbColumns) {
        qCritical() << "Bad maze coordinates";
    }
    return m_cells[p_row][p_column];
}

QPoint Maze::getCoords(Cell *p_cell) const
{
    for (int i = 0; i < m_nbRows; ++i) {
        for (int j = 0; j < m_nbColumns; ++j) {
            if (&m_cells[i][j] == p_cell) {
                return QPoint(j, i);
            }
        }
    }
    return QPoint();
}

int Maze::getRowFromY(const qreal p_y) const
{
    return (int)(p_y / Cell::SIZE);
}

int Maze::getColFromX(const qreal p_x) const
{
    return (int)(p_x / Cell::SIZE);
}

int Maze::getNbColumns() const
{
    return m_nbColumns;
}

int Maze::getNbRows() const
{
    return m_nbRows;
}

int Maze::getNbElem() const
{
    return m_nbElem;
}

int Maze::getTotalNbElem() const
{
    return m_totalNbElem;
}

QPoint Maze::getResurrectionCell() const
{
    return m_resurrectionCell;
}
