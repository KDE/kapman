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

#include "kapman.h"

const int Kapman::SPEED = 1;

Kapman::Kapman() : m_x(0), m_y(0), m_xSpeed(0), m_ySpeed(0) {

}

Kapman::~Kapman() {

}

void Kapman::goUp() {
	m_xSpeed = 0;
	m_ySpeed = -SPEED;
}

void Kapman::goDown() {
	m_xSpeed = 0;
	m_ySpeed = SPEED;
}

void Kapman::goRight() {
	m_xSpeed = SPEED;
	m_ySpeed = 0;
}

void Kapman::goLeft() {
	m_xSpeed = -SPEED;
	m_ySpeed = 0;
}

void Kapman::move() {
	m_x += m_xSpeed;
	m_y += m_ySpeed;
	emit(moved(m_x, m_y));
}

int Kapman::getX() const {
	return m_x;
}

int Kapman::getY() const {
	return m_y;
}
