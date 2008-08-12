/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Nathalie Liesse <nathalie.liesse@gmail.com>
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

#ifndef __MAZEPARSER_H
#define __MAZEPARSER_H

#include "maze.h"

#include <QXmlDefaultHandler>

/**
 * @brief This class handles XML reader events in order to initialize the Maze properties.
 */
class MazeParser : public QXmlDefaultHandler {
	
	private:

		/** The Maze to initialize */
		Maze* m_maze;
		QString m_buffer;
		int m_counterRows;
	public:

		/**
		 * Creates a new MazeParser.
		 * @param p_maze the Maze to initialize
		 */
		 MazeParser(Maze* p_maze);
		
		/**
		 * Deletes the MazeParser instance.
		 */
		~MazeParser();
		
		/**
		* Implement QXmlDefaultHandler::characters
		*/
		bool characters(const QString & ch );

		/**
		 * Implements QXmlDefaultHandler::startElement()
		 */
		bool startElement(const QString&, const QString&, const QString& p_qName, const QXmlAttributes& p_atts);
		
		/**
		* Implements QXmlDefaultHandler::endElement()
		*/
		bool endElement(const QString &, const QString &, const QString & p_qName );

};

#endif

