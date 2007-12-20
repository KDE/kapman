/* This file is part of Kapman.
   Created by Alexandre GALINIER <alex.galinier@hotmail.com>

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

#ifndef __GHOST_H
#define __GHOST_H

#include "character.h"

/**
 * This class represents the ghost
 */
class Ghost : public Character {

	Q_OBJECT

	public:

		/** The Ghost moving speed */
 		static const qreal SPEED;

	private:

		/** Ghost coordinates */
// 		qreal m_x, m_y;

		/** Ghost speed */
// 		qreal m_xSpeed, m_ySpeed;
		
		/** URL to the ghost's image */
		QString m_imageURL;

	public:

		/**
		 * Creates a new Ghost instance
		 */
		Ghost(qreal p_x, qreal p_y, QString p_imageURL);

		/**
		 * Deletes the Ghost instance
		 */
		~Ghost();

		/**
		 * Makes the Ghost go up
		 */
		void goUp();

		/**
		 * Makes the Ghost go down
		 */
		void goDown();

		/**
		 * Makes the Ghost go to the right
		 */
		void goRight();

		/**
		 * Makes the Ghost go to the left
		 */
		void goLeft();

		/**
		 * @return the URL to the ghost's image
		 */
		QString getImageURL() const;

};

#endif
