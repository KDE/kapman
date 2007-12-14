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

#ifndef __GHOST_H
#define __GHOST_H

#include <QObject>

/**
 * This class represents the ghost
 */
class Ghost : public QObject {

	Q_OBJECT

	public:

		/** The Ghost moving speed */
		static const qreal SPEED;

	private:

		/** Ghost coordinates */
		qreal m_x, m_y;

		/** Ghost speed */
		qreal m_xSpeed, m_ySpeed;
		
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
		 * Moves the Ghost function of its coordinates and speed
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
		 * @return the x speed coordinate
		 */
		qreal getXSpeed() const;

		/**
		 * @return the y speed coordinate
		 */
		qreal getYSpeed() const;
		
		/**
		 * @return the URL to the ghost's image
		 */
		QString getImageURL() const;
		
	signals:

		/**
		 * On Ghost move
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void moved(qreal p_x, qreal p_y);

	public slots:

		/**
		 * Makes the Ghost "circle around" the maze when reaching a border
		 * @param p_newX the new X coordinate
		 * @param p_newY the new Y coordinate
		 */
		void changeMazeSide(qreal p_newX, qreal p_newY);
};

#endif
