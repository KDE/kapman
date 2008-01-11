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
#include <KDebug>
#include "maze.h"
#include "mazeparser.h"

Maze::Maze() {
	MazeParser mazeParser(this);

	QFile* mazeXmlFile = new QFile(KStandardDirs::locate("appdata", "defaultmaze.xml"));
	QXmlInputSource source(mazeXmlFile);

	QXmlSimpleReader reader;
	reader.setContentHandler(&mazeParser);

	reader.parse(source);
}
	
Maze::~Maze() {
	for(int i = 0 ; i < m_nbRows; i++) {
		delete[] m_cells[i];
	}
	delete[] m_cells;
}

void Maze::init(int p_nbRows, int p_nbColumns) {
	m_nbRows = p_nbRows;
	m_nbColumns = p_nbColumns;
	m_cells = new Cell*[m_nbRows];
	for(int i = 0; i < m_nbRows; i++) {
		m_cells[i] = new Cell[m_nbColumns];
	}
}

void Maze::setCellType(int p_row, int p_column, Cell::CellType p_type) {
	if (p_row < 0 || p_row >= m_nbRows ||
		p_column < 0 || p_column >= m_nbColumns) {
		kDebug() << "Bad maze coordinates";
	}
	m_cells[p_row][p_column].setType(p_type);
}

Cell Maze::getCell(int p_row, int p_column) {
	if (p_row < 0 || p_row >= m_nbRows ||
		p_column < 0 || p_column >= m_nbColumns) {
		kDebug() << "Bad maze coordinates";
	}
	return m_cells[p_row][p_column];
}

int Maze::getRowFromY(qreal p_y) {
	return (int)(p_y / Cell::SIZE);
}

int Maze::getColFromX(qreal p_x) {
	return (int)(p_x / Cell::SIZE);
}
