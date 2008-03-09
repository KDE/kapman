/*
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

#include "maze.h"
#include <KDebug>
#include <KStandardDirs>
#include "mazeparser.h"

Maze::Maze() : m_totalNbElem(0), m_nbElem(0) {
	MazeParser mazeParser(this);

	QFile mazeXmlFile(KStandardDirs::locate("appdata", "defaultmaze.xml"));
	QXmlInputSource source(&mazeXmlFile);

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

void Maze::setCellType(int p_row, int p_column, Cell::CellType p_type, Element * p_element) {
	if (p_row < 0 || p_row >= m_nbRows || p_column < 0 || p_column >= m_nbColumns) {
		kDebug() << "Bad maze coordinates";
	}
	m_cells[p_row][p_column].setType(p_type);
	m_cells[p_row][p_column].setElement(p_element);
	if (p_element != NULL) {
		m_totalNbElem++;
		m_nbElem++;
	}
}

void Maze::decrementNbElem() {
	m_nbElem--;
	if (m_nbElem == 0) {
		emit(allElementsEaten());
	}
}

void Maze::resetNbElem() {
	m_nbElem = m_totalNbElem;
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

int Maze::getNbColumns() {
	return m_nbColumns;
}

int Maze::getNbRows() {
	return m_nbRows;
}

int Maze::getNbElem() {
	return m_nbElem;
}

int Maze::getTotalNbElem() {
	return m_totalNbElem;
}

