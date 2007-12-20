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

#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <QObject>

/**
 * This class describes the main characteristics of the Kapman and the ghosts
 */
class Character : public QObject {

	Q_OBJECT

	protected:

		/** Character coordinates */
		qreal m_x, m_y;

		/** Character speed */
		qreal m_xSpeed, m_ySpeed;

	public:

		/**
		 * Creates a new Character instance
		 * @param p_x the initial x coordinate
		 * @param p_y the initial y coordinate
		 */
		Character(qreal p_x, qreal p_y);

		/**
		 * Deletes the Character instance
		 */
		~Character();

		/**
		 * Makes the Character go up
		 */
// 		void goUp();

		/**
		 * Makes the Character go down
		 */
// 		void goDown();

		/**
		 * Makes the Character go to the right
		 */
// 		void goRight();

		/**
		 * Makes the Character go to the left
		 */
// 		void goLeft();

		/**
		 * Moves the Character function of its coordinates and speed
		 */
		void move();

		/**
		 * @return the x-coordinate
		 */
		qreal getX() const;

		/**
		 * @return the y-coordinate
		 */
		qreal getY() const;

		/**
		 * @return the x speed value
		 */
		qreal getXSpeed() const;

		/**
		 * @return the y speed value
		 */
		qreal getYSpeed() const;

		/**
		 * Sets the x coordinate to the given value
		 * @param p_x the new x coordinate to set
		 */
		void setX(qreal p_x);

		/**
		 * Sets the y coordinate to the given value
		 * @param p_y the new y coordinate to set
		 */
		void setY(qreal p_y);
		
		/**
		 * Set the X speed attribute
		 * @param p_xSpeed the x speed attribute
		 */
		 void setXSpeed(qreal p_xSpeed);
		 
		 /**
		 * Set the Y speed attribute
		 * @param p_ySpeed the y speed attribute
		 */
		 void setYSpeed(qreal p_ySpeed);

	signals:

		/**
		 * On Character move
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void moved(qreal p_x, qreal p_y);

	public slots:

		/**
		 * Makes the Character "circle around" the maze when reaching a border
		 * @param p_newX the new X coordinate
		 * @param p_newY the new Y coordinate
		 * TODO re-develop it according to new architecture
		 */
		//void changeMazeSide(qreal p_newX, qreal p_newY);
};

#endif
