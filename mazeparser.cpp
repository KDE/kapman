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
#include <KStandardDirs>
#include "element.h"
#include "pill.h"
#include "energizer.h"

MazeParser::MazeParser(Maze* p_maze) {
	m_maze = p_maze;
}

MazeParser::~MazeParser() {
}

bool MazeParser::startElement(const QString&, const QString&, const QString& p_qName, const QXmlAttributes& p_atts) {
	
	if(p_qName == "Maze") {
		int nbRows = 0;
		int nbColumns = 0;
		
		for(int i = 0 ; i < p_atts.count() ; i++) {
			if(p_atts.qName(i) == "nbRows") {
				nbRows = p_atts.value(i).toInt();
			}
			
			if(p_atts.qName(i) == "nbColumns") {
				nbColumns = p_atts.value(i).toInt();
			}
		}
		
		m_maze->init(nbRows, nbColumns);
	}
	
	if(p_qName == "Cell") {
		int rowIndex = 0;
		int columnIndex = 0;
		int cellType = 0;
		int itemType = 0;
		
		for(int i = 0 ; i < p_atts.count() ; i++) {
			if(p_atts.qName(i) == "rowIndex") {
				rowIndex = p_atts.value(i).toInt();
			}
			
			if(p_atts.qName(i) == "columnIndex") {
				columnIndex = p_atts.value(i).toInt();
			}
			
			if(p_atts.qName(i) == "allowedMove") {
				cellType = p_atts.value(i).toInt();
			}

			if(p_atts.qName(i) == "item") {
				itemType = p_atts.value(i).toInt();
			}
		}

		switch(itemType)
		{
			case 0:
				m_maze->setCellType(rowIndex, columnIndex, (Cell::CellType)cellType, NULL);
				break;
			case 1:
				m_maze->setCellType(rowIndex, columnIndex, (Cell::CellType)cellType, new Pill(rowIndex, columnIndex, m_maze, KStandardDirs::locate("appdata", "pill_test.svg")));
				break;
			case 2:
				m_maze->setCellType(rowIndex, columnIndex, (Cell::CellType)cellType, new Energizer(rowIndex, columnIndex, m_maze, KStandardDirs::locate("appdata", "energizer_test.svg")));
				break;
		}

	}
	
	return true;
}
