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

#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <QObject>
#include "maze.h"

class Kapman;

/**
 * This class describes the main characteristics of a game element (character or item)
 */
class Element : public QObject {

	Q_OBJECT

	protected:

		/** Element coordinates */
		qreal m_x, m_y;

		/** The maze the element is on */
		Maze* m_maze;

		/** The Url of the element */
		QString m_imageUrl;

	public:

		/**
		 * Creates a new Element instance
		 * @param p_x the initial x coordinate
		 * @param p_y the initial y coordinate
		 * @param p_maze the maze the element is on
		 */
		Element(qreal p_x, qreal p_y, Maze* p_maze);

		/**
		 * Deletes the Element instance
		 */
		~Element();

		/**
		 * Computes an action on a collision with the kapman
		 * @param p_element the kapman that collides with this element
		 */
		virtual void doActionOnCollision(Kapman* p_kapman);

		/**
		 * @return the type of the Element
		 */
		QString getImageUrl();

		/**
		 * @return the type of the Element
		 */
		void setImageUrl(QString p_imageUrl);

		/**
		 * @return the x-coordinate
		 */
		qreal getX() const;

		/**
		 * @return the y-coordinate
		 */
		qreal getY() const;

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
		 * On Character move
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void moved(qreal p_x, qreal p_y);
};

#endif