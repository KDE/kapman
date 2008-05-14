/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
 * Copyright 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>
 * Copyright 2007-2008 Johann Hingue <yoan1703@hotmail.fr>
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

#include "bonus.h"
#include "kapman.h"

Bonus::Bonus(qreal p_x, qreal p_y, Maze* p_maze, int p_points) : Element(p_x, p_y, p_maze) {
	m_points = p_points;
	m_type = Element::BONUS;
}

Bonus::~Bonus() {

}

void Bonus::doActionOnCollision(Kapman* p_kapman) {
	p_kapman->winPoints(this);
}

void Bonus::setPoints(const int p_points) {
	m_points = p_points;
}

