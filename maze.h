/* This file is part of Kapman.
   Created by Pierre-Benoît Besse <besse.pb@gmail.com>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
*/

#ifndef __MAZE_H
#define __MAZE_H

#include <QObject>

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
		int** m_mazeArray;
	
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
		 * Sets the allowed move value of a cell
		 * @param p_row the cell row
		 * @param p_column the cell column
		 * @param p_value the allowed move value :
		 *				  0 if not allowed, 1 if allowed
		 */
		void setAllowedMove(int p_row, int p_column, int p_value);
};

#endif
