/**
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	
	public:
	
		/** The elements possible types */
		enum ElementType {
			KAPMAN = 0,
			GHOST = 1,
			PILL = 2,
			ENERGYZER = 3,
			BONUS = 4
		};
		
	protected:
	
		/** The element's type */
		ElementType m_type;

		/** Element coordinates */
		qreal m_x, m_y;

		/** The maze the element is on */
		Maze* m_maze;

		/** The Url of the element */
		QString m_imageUrl;
		
		/** Points won when the element is eaten */
		int m_points;

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
		 * @param p_kapman the kapman that collides with this element
		 */
		virtual void doActionOnCollision(Kapman* p_kapman);

		/**
		 * @return the type of the Element
		 */
		QString getImageUrl() const;
		
		/**
		 * @return the points won when the element is eaten
		 */
		int getPoints() const;
		
		/**
		 * @return the element type 
		 */
		Element::ElementType getType() const;

		/**
		 * Sets the element image
		 * @param p_imageUrl the image to set
		 */
		void setImageUrl(const QString & p_imageUrl);

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
