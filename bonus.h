/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
 * Copyright 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>
 * Copyright 2007-2008 Johann Hingue <yoan1703@hotmail.fr>
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

#ifndef BONUS_H
#define BONUS_H

#include "element.h"

/**
 * @brief This class represents a Bonus for Kapman.
 */
class Bonus : public Element {

	public:

		/**
		 * Creates a new Bonus instance.
		 * @param p_x the initial x-coordinate
		 * @param p_y the initial y-coordinate
		 * @param p_maze a reference to the Maze the Bonus will be on
		 * @param p_points the value of the Bonus
		 */
		Bonus(qreal p_x, qreal p_y, Maze* p_maze, int p_points);

		/**
		 * Deletes the Bonus instance.
		 */
		~Bonus();

		/**
		 * Computes an action on a collision with the Kapman.
		 * @param p_kapman the Kapman instance that collides with the Bonus
		 */
		void doActionOnCollision(Kapman* p_kapman);
		
		/**
		 * Sets the given value to the Bonus.
		 * @param p_points the value of the Bonus
		 */
		void setPoints(const int p_points);
};

#endif

