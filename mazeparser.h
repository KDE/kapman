/* This file is part of Kapman.
   Created by Nathalie Liesse <nathalie.liesse@gmail.com>

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

#ifndef __MAZEPARSER_H
#define __MAZEPARSER_H

#include <QXmlDefaultHandler>
#include "maze.h"

/**
 * This class initializes the maze from an xml file
 */
class MazeParser : public QXmlDefaultHandler {
	
	private:

		/** The maze to initialize */
		Maze* m_maze;
	
	public:
		/**
		 * Creates a new MazeParser
		 * @param p_maze the maze to initialize
		 */
		 MazeParser(Maze* p_maze);
		
		/**
		 * Deletes the MazeParser instance
		 */
		~MazeParser();
		
		/**
		 * Called each time a start element tag is met
		 * Implements QXmlDefaultHandler::startElement
		 */
		bool startElement(const QString&, const QString&,
						  const QString& p_qName, const QXmlAttributes& p_atts);
};

#endif
