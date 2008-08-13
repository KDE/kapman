/*
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "element.h"

Element::Element(qreal p_x, qreal p_y, Maze* p_maze) : m_xInit(p_x), m_yInit(p_y),  m_maze(p_maze) {
	m_points = 0;
	initCoordinate();
}

Element::~Element() {
}

void Element::doActionOnCollision(Kapman* p_kapman) {
	// Do nothing by default : will be redefined within the subclasses
}

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

int Element::getPoints() const {
	return m_points;
}

Element::Type Element::getType() const {
	return m_type;
}

QString Element::getImageUrl() const {
	return m_imageUrl;
}

void  Element::setImageUrl(const QString & p_imageUrl){
	m_imageUrl = p_imageUrl;
}

void Element::initCoordinate(){
	setX(m_xInit);
	setY(m_yInit);
}
