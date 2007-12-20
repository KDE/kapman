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

const qreal Kapman::SPEED = 2.0;

Kapman::Kapman(qreal p_x, qreal p_y) : Character(p_x, p_y) {
	// Makes the Kapman move as soon as the game is created
	goLeft();
}

Kapman::~Kapman() {

}

void Kapman::goUp() {
	m_askedXSpeed = 0;
	m_askedYSpeed = -SPEED;
}

void Kapman::goDown() {
	m_askedXSpeed = 0;
	m_askedYSpeed = SPEED;
}

void Kapman::goRight() {
	m_askedXSpeed = SPEED;
	m_askedYSpeed = 0;
}

void Kapman::goLeft() {
	m_askedXSpeed = -SPEED;
	m_askedYSpeed = 0;
}

void Kapman::updateDirection() {
	setXSpeed(m_askedXSpeed);
	setYSpeed(m_askedYSpeed);
	m_askedXSpeed = 0;
	m_askedYSpeed = 0;
}

void Kapman::stopMoving() {
	setXSpeed(0);
	setYSpeed(0);
	m_askedXSpeed = 0;
	m_askedYSpeed = 0;
}

/** Accessors */
qreal Kapman::getAskedXSpeed() const {
	return m_askedXSpeed;
}

qreal Kapman::getAskedYSpeed() const {
	return m_askedYSpeed;
}
