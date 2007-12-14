/* This file is part of Kapman.
   Created by Thomas Gallinari <tg8187@yahoo.fr>

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

#ifndef __CELL_H
#define __CELL_H

#include <QtGlobal>

/**
 * This class represents a cell of the Kapman maze
 */
class Cell {

	public:

		/** The cell side size */
		static const qreal SIZE;

		/** The cell possible types */
		enum CellType {
			WALL = 0,
			CORRIDOR = 1
		};

	private:

		/** The cell type */
		CellType m_type;

	public:

		/**
		 * Creates a new Cell instance
		 */
		Cell();

		/**
		 * Deletes the Cell instance
		 */
		~Cell();

		/**
		 * @return the cell type
		 */
		CellType getType();

		/**
		 * Sets the cell type
		 * @param p_type the new type to set
		 */
		void setType(CellType p_type);
};

#endif
