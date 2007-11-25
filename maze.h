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
		 * Initializes the maze from an XML file
		 */
		void init();
		
};

#endif
