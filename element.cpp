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

#include "element.h"

Element::Element(qreal p_x, qreal p_y, Maze* p_maze) :	m_x(p_x), m_y(p_y), m_maze(p_maze) {

}

Element::~Element() {

}

void Element::doActionOnCollision(Kapman* p_kapman) {
	// Do nothing by default : will be redefined within the subclasses
}

/** Accessors */
qreal Element::getX() const {
	return m_x;
}

qreal Element::getY() const {
	return m_y;
}

void Element::setX(qreal p_x) {
	m_x = p_x;
	emit(moved(m_x, m_y));
}

void Element::setY(qreal p_y) {
	m_y = p_y;
	emit(moved(m_x, m_y));
}
