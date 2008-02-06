/* This file is part of Kapman.
   Created by Gaël Courcelle & Allanic Alexia <tg8187@yahoo.fr>

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

#include "pill.h"
#include "kapman.h"

const qreal Pill::POINTS = 10.0;

Pill::Pill(qreal p_x, qreal p_y, Maze* p_maze, QString p_imageUrl) : Element(p_x, p_y, p_maze) {
	Element::setImageUrl(p_imageUrl);
}

Pill::~Pill() {

}

void Pill::doActionOnCollision(Kapman* p_kapman) {
	//TO DO
	p_kapman->winPoints(POINTS, this->getX(), this->getY());
}


