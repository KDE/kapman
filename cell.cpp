/**
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
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

#include "cell.h"
#include "element.h"

const qreal Cell::SIZE = 20.0;

Cell::Cell() : m_type(Cell::WALL) {

}

Cell::~Cell() {
	m_element = NULL;
	delete m_element;	
}

Cell::CellType Cell::getType() {
	return m_type;
}

void Cell::setType(Cell::CellType p_type) {
	m_type = p_type;
}

Element * Cell::getElement() {
	return m_element;
}

void Cell::setElement(Element * p_element) {
	m_element = p_element;
}
