/*
 * Copyright 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MAZE_H
#define __MAZE_H

#include <QObject>
#include <QList>
#include <QPoint>
#include "cell.h"

/**
 * This class represents the maze of kapman
 */
class Maze : public QObject {

	Q_OBJECT

	public:

		/** The cell where ghosts go back when they have been eaten */
		const static QPoint GHOST_RESURRECT_CELL;
	
	private:

		/** Number of rows of m_mazeArray */
		int m_nbRows;
		
		/** Number of columns of m_mazeArray */
		int m_nbColumns;
		
		/** Maze matrix */
		Cell** m_cells;

		/** Total number of elements on the maze */
		int m_totalNbElem;

		/** Number of remaining elements on the maze */
		int m_nbElem;

	public:

		/**
		 * Creates a new Maze instance
		 */
		Maze();

		/**
		 * Deletes the Maze instance
		 */
		~Maze();
		
		/**
		 * Initializes the maze matrix
		 * @param p_nbRows the number of rows
		 * @param p_nbColumns the number of columns
		 */
		void init(int p_nbRows, int p_nbColumns);

		/**
		 * Sets the given cell type and element
		 * @param p_row the cell row
		 * @param p_column the cell column
		 * @param p_type the cell new type
		 * @param p_element reference to the element that is on the cell
		 */
		void setCellType(int p_row, int p_column, Cell::CellType p_type, Element * p_element);

		/**
		 * Decrements the number of remaining elements
		 */
		void decrementNbElem();

		/**
		 * Resets the number of remaining elements
		 */
		void resetNbElem();

		/**
		 * @param p_row the starting cell row index
		 * @param p_colum the starting cell column index
		 * @return a list of cell coordinates to go to the ghost camp from the given coordinates, using A* algorithm
		 */
		QList<QPoint> getPathToGhostCamp(const int p_row, const int p_column);

		/**
		 * @param p_row the row index
		 * @param p_column the column index
		 * @return the cell at the given row and column
		 */
		Cell getCell(int p_row, int p_column);

		/**
		 * @param p_cell the searched cell
		 * @return the coordinates (row, column) of the given cell pointer
		 */
		QPoint getCoords(Cell* p_cell) const;

		/**
		 * @param p_y the y coordinate to convert into row index
		 * @return the row index corresponding to the given y coordinate
		 */
		int getRowFromY(qreal p_y);

		/**
		 * @param p_x the x coordinate to convert into column index
		 * @return the column index corresponding to the given x coordinate
		 */
		int getColFromX(qreal p_x);
		
		/**
		 * @return the number of colums of the maze
		 */
		int getNbColumns();
		 
		/**
		 * @return the number of rows of the maze
		 */
		int getNbRows();
		
		/**
		 * @return the number of remaining elements on the maze
		 */
		int getNbElem();
		
		/**
		 * @return Total number of elements on the maze
		 */
		int getTotalNbElem();

	signals:

		/**
		 * Emitted when all the elements on the maze have been eaten
		 */
		void allElementsEaten();
};

#endif
