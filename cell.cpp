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

#include "cell.h"

const qreal Cell::SIZE = 20.0;

Cell::Cell() : m_type(Cell::WALL) {

}

Cell::~Cell() {

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
