/*
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

#include "mazeparser.h"
#include "element.h"
#include "pill.h"
#include "energizer.h"
#include <KDebug>
#include <KStandardDirs>

MazeParser::MazeParser(Maze* p_maze) {
	m_maze = p_maze;
	m_counterRows = 0;
}

MazeParser::~MazeParser() {
}

bool MazeParser::characters(const QString & ch ){
	m_buffer = ch;
	return true;
}

bool MazeParser::startElement(const QString&, const QString&, const QString& p_qName, const QXmlAttributes& p_atts) {
	int nbRows = 0;
	int nbColumns = 0;
	if (p_qName == "Maze") {
		// Initialize the number of rows and columns
		for (int i = 0; i < p_atts.count(); i++) {
			if (p_atts.qName(i) == "rowCount") {
				nbRows = p_atts.value(i).toInt();
			}
			if (p_atts.qName(i) == "colCount") {
				nbColumns = p_atts.value(i).toInt();
			}
		}
		// Create the Maze matrix
		m_maze->init(nbRows, nbColumns);
	}
	
	return true;
}

bool MazeParser::endElement(const QString &, const QString &, const QString & p_qName ){
	if(p_qName == "Row")
	{
		for (int i=0; i<m_buffer.length();i++)
		{
			switch(m_buffer.at(i).toAscii()){
				case '|':
				case '=': m_maze->setCellType(m_counterRows,i,Cell::WALL);
					break;
				case ' ': m_maze->setCellType(m_counterRows,i,Cell::CORRIDOR);
					break;
				case '.': m_maze->setCellType(m_counterRows,i,Cell::CORRIDOR);
					m_maze->setCellElement(m_counterRows, i,
							new Pill(m_counterRows, i, m_maze, KStandardDirs::locate("appdata", "pill.svg")));
					break; 
				case '@': m_maze->setCellType(m_counterRows,i,Cell::CORRIDOR);
					break;
				case 'o':m_maze->setCellType(m_counterRows,i,Cell::CORRIDOR);
					m_maze->setCellElement(m_counterRows, i,
							new Energizer(m_counterRows, i, m_maze, KStandardDirs::locate("appdata", "energizer.svg")));
					break;
				case 'x':m_maze->setCellType(m_counterRows,i,Cell::GHOSTCAMP);
					break;
			}
		}
		m_counterRows ++;
	}
	return true;
}



