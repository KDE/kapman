/**
 * Copyright 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
 * Copyright 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>
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

#ifndef __PILL_H
#define __PILL_H
#include "element.h"

/**
 * This class represents a pill of the Kapman maze
 */
class Pill : public Element {

	public:

		/** The pill's points */
		static const int POINTS;


	public:

		/**
		 * Creates a new Pill instance
		 */
		Pill(qreal p_x, qreal p_y, Maze* p_maze, QString & p_imageUrl);

		/**
		 * Deletes the Pills instance
		 */
		~Pill();

		/**
		 * Computes an action on a collision with the kapman
		 * @param p_element the kapman that collides with this element
		 */
		void doActionOnCollision(Kapman* p_kapman);

};

#endif
