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

#include <QGraphicsScene>
#include "kapman.h"

const qreal Kapman::SPEED = 2.0;

Kapman::Kapman(qreal p_x, qreal p_y) :
		m_x(p_x), m_y(p_y), m_xSpeed(-SPEED), m_ySpeed(0),
		m_askedXSpeed(0), m_askedYSpeed(0) {

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
	m_xSpeed = m_askedXSpeed;
	m_ySpeed = m_askedYSpeed;
	m_askedXSpeed = 0;
	m_askedYSpeed = 0;
}

void Kapman::move() {
	m_x += m_xSpeed;
	m_y += m_ySpeed;
	
	emit(moved(m_x, m_y));
}

void Kapman::stopMoving() {
	m_xSpeed = 0;
	m_ySpeed = 0;
	m_askedXSpeed = 0;
	m_askedYSpeed = 0;
}

/** Accessors */
qreal Kapman::getX() const {
	return m_x;
}

qreal Kapman::getY() const {
	return m_y;
}

qreal Kapman::getXSpeed() const {
	return m_xSpeed;
}

qreal Kapman::getYSpeed() const {
	return m_ySpeed;
}

qreal Kapman::getAskedXSpeed() const {
	return m_askedXSpeed;
}

qreal Kapman::getAskedYSpeed() const {
	return m_askedYSpeed;
}

void Kapman::setX(qreal p_x) {
	m_x = p_x;
	emit(moved(m_x, m_y));
}

void Kapman::setY(qreal p_y) {
	m_y = p_y;
	emit(moved(m_x, m_y));
}

/** SLOTS */
void Kapman::changeMazeSide(qreal p_newX, qreal p_newY) {
	m_x = p_newX;
	m_y = p_newY;
}
