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

#ifndef __KAPMAN_H
#define __KAPMAN_H

#include <QObject>

/**
 * This class represents the main character of the game
 */
class Kapman : public QObject {

	Q_OBJECT

	public:

		/** The Kapman moving speed */
		static const qreal SPEED;

	private:

		/** Kapman coordinates */
		qreal m_x, m_y;

		/** Kapman speed */
		qreal m_xSpeed, m_ySpeed;

		/** Kapman required speed */
		qreal m_askedXSpeed, m_askedYSpeed;

	public:

		/**
		 * Creates a new Kapman instance
		 * @param p_x the initial x coordinate
		 * @param p_y the initial y coordinate
		 */
		Kapman(qreal p_x, qreal p_y);

		/**
		 * Deletes the Kapman instance
		 */
		~Kapman();

		/**
		 * Makes the Kapman go up
		 */
		void goUp();

		/**
		 * Makes the Kapman go down
		 */
		void goDown();

		/**
		 * Makes the Kapman go to the right
		 */
		void goRight();

		/**
		 * Makes the Kapman go to the left
		 */
		void goLeft();

		/**
		 * Updates the Kapman direction with the asked direction
		 */
		void updateDirection();

		/**
		 * Moves the Kapman function of its coordinates and speed
		 */
		void move();

		/**
		 * Stops moving the Kapman
		 */
		void stopMoving();

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
		 * @return the asked x speed value
		 */
		qreal getAskedXSpeed() const;

		/**
		 * @return the asked y speed value
		 */
		qreal getAskedYSpeed() const;

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

	signals:

		/**
		 * On Kapman move
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void moved(qreal p_x, qreal p_y);

	public slots:

		/**
		 * Makes the kapman "circle around" the maze when reaching a border
		 * @param p_newX the new X coordinate
		 * @param p_newY the new Y coordinate
		 */
		void changeMazeSide(qreal p_newX, qreal p_newY);
};

#endif
