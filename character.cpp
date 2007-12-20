/* This file is part of Kapman.
   Created by Pierre-Benoit Besse <besse.pb@gmail.com>

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

#include "character.h"

// const qreal Character::SPEED = 2.0;

Character::Character(qreal p_x, qreal p_y) :
		m_x(p_x), m_y(p_y), m_xSpeed(0), m_ySpeed(0) {

}

Character::~Character() {

}

// void Character::goUp() {
// 	m_xSpeed = 0;
// 	m_ySpeed = -SPEED;
// }
// 
// void Character::goDown() {
// 	m_xSpeed = 0;
// 	m_ySpeed = SPEED;
// }
// 
// void Character::goRight() {
// 	m_xSpeed = SPEED;
// 	m_ySpeed = 0;
// }
// 
// void Character::goLeft() {
// 	m_xSpeed = -SPEED;
// 	m_ySpeed = 0;
// }

void Character::move() {
	m_x += m_xSpeed;
	m_y += m_ySpeed;
	
	emit(moved(m_x, m_y));
}

/** Accessors */
qreal Character::getX() const {
	return m_x;
}

qreal Character::getY() const {
	return m_y;
}

qreal Character::getXSpeed() const {
	return m_xSpeed;
}

qreal Character::getYSpeed() const {
	return m_ySpeed;
}

void Character::setX(qreal p_x) {
	m_x = p_x;
	emit(moved(m_x, m_y));
}

void Character::setY(qreal p_y) {
	m_y = p_y;
	emit(moved(m_x, m_y));
}

void Character::setXSpeed(qreal p_xSpeed) {
	m_xSpeed = p_xSpeed;
}

void Character::setYSpeed(qreal p_ySpeed) {
	m_ySpeed = p_ySpeed;
}

/** SLOTS */
// void Character::changeMazeSide(qreal p_newX, qreal p_newY) {
// 	m_x = p_newX;
// 	m_y = p_newY;
// }
