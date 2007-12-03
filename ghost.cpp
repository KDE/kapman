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

#include "ghost.h"

const qreal Ghost::SPEED = 2.5;

Ghost::Ghost(qreal p_x, qreal p_y, QString p_imageURL) : m_xSpeed(0), m_ySpeed(0) {
	m_x = p_x;
	m_y = p_y;
	m_imageURL = p_imageURL;
}

Ghost::~Ghost() {

}

void Ghost::goUp() {
	m_xSpeed = 0;
	m_ySpeed = -SPEED;
}

void Ghost::goDown() {
	m_xSpeed = 0;
	m_ySpeed = SPEED;
}

void Ghost::goRight() {
	m_xSpeed = SPEED;
	m_ySpeed = 0;
}

void Ghost::goLeft() {
	m_xSpeed = -SPEED;
	m_ySpeed = 0;
}

void Ghost::move() {
	m_x += m_xSpeed;
	m_y += m_ySpeed;
	
	emit(moved(m_x, m_y));
}

/** Accessors */
qreal Ghost::getSPEED() const {
	return SPEED;
}

qreal Ghost::getX() const {
	return m_x;
}

qreal Ghost::getY() const {
	return m_y;
}

qreal Ghost::getXSpeed() const {
	return m_xSpeed;
}

qreal Ghost::getYSpeed() const {
	return m_ySpeed;
}

QString Ghost::getImageURL() const  {
	return m_imageURL;
}

/** SLOTS */
void Ghost::changeMazeSide(qreal p_newX, qreal p_newY) {
	m_x = p_newX;
	m_y = p_newY;
}
