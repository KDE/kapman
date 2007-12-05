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

#include <KStandardDirs>
#include "maze.h"
#include "mazeparser.h"
#include <KDebug>

Maze::Maze() {
	MazeParser mazeParser(this);
	
	QFile* mazeXmlFile = new QFile(
		KStandardDirs::locate("appdata", "defaultmaze.xml"));
	QXmlInputSource source(mazeXmlFile);
	
	QXmlSimpleReader reader;
	reader.setContentHandler(&mazeParser);
	
	reader.parse(source);
}
	
Maze::~Maze() {
	for(int i = 0 ; i < m_nbRows; i++) {
		delete[] m_mazeArray[i];
	}
	delete[] m_mazeArray;
}

void Maze::init(int p_nbRows, int p_nbColumns) {
	m_nbRows = p_nbRows;
	m_nbColumns = p_nbColumns;
	m_mazeArray = new int*[m_nbRows];
	for(int i = 0; i < m_nbRows; i++) {
		m_mazeArray[i] = new int[m_nbColumns];
	}
}

void Maze::setAllowedMove(int p_row, int p_column, int p_value) {
	if (p_row >= 0 && p_row < m_nbRows &&
		p_column >= 0 && p_column < m_nbColumns) {
		m_mazeArray[p_row][p_column] = p_value;
	}
}
