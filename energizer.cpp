/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
 * Copyright 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>
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

#include "energizer.h"
#include "kapman.h"

const int Energizer::POINTS = 50;

Energizer::Energizer(qreal p_x, qreal p_y, Maze* p_maze, const QString& p_imageUrl) :  Element(p_x, p_y, p_maze) {
	Element::setImageUrl(p_imageUrl);
	m_points = 50;
	m_type = Element::ENERGYZER;
}

Energizer::~Energizer() {
}

void Energizer::doActionOnCollision(Kapman* p_kapman) {
	p_kapman->winPoints(this);
	// Tell to the maze that an element was eaten
	m_maze->decrementNbElem();
}

