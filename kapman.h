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

	private:

		/** The Kapman moving speed */
		static const int SPEED;

		/** Kapman coordinates */
		int m_x, m_y;

		/** Kapman speed */
		int m_xSpeed, m_ySpeed;

	public:

		/**
		 * Creates a new Kapman instance
		 */
		Kapman();

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
		 * Moves the Kapman function of its coordinates and speed
		 */
		void move();

		/**
		 * @return the x-coordinate
		 */
		int getX() const;

		/**
		 * @return the y-coordinate
		 */
		int getY() const;

	signals:

		/**
		 * On Kapman move
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void moved(int p_x, int p_y);
};

#endif
