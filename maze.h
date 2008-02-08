/**
 * Copyright 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>
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
#include "cell.h"

/**
 * This class represents the maze of kapman
 */
class Maze : public QObject {

	Q_OBJECT
	
	private:
		
		/** Number of rows of m_mazeArray */
		int m_nbRows;
		
		/** Number of columns of m_mazeArray */
		int m_nbColumns;
		
		/** Maze matrix */
		Cell** m_cells;
	
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
		 * @param p_rows the number of rows
		 * @param p_columns the number of columns
		 */
		void init(int p_nbRows, int p_nbColumns);

		/**
		 * Sets the given cell type
		 * @param p_row the cell row
		 * @param p_column the cell column
		 * @param p_type the cell new type
		 */
		void setCellType(int p_row, int p_column, Cell::CellType p_type, Element * p_element);

		/**
		 * @param p_row the row index
		 * @param p_column the column index
		 * @return the cell at the given row and column
		 */
		Cell getCell(int p_row, int p_column);

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
};

#endif
