/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
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

#ifndef ENERGIZER_H
#define ENERGIZER_H


#include "element.h"

/**
 * @brief This class represents an energizer enabling to eat Ghosts.
 */
class Energizer : public Element {

	Q_OBJECT

	public:

		/** The value of an Energyzer */
		static const int POINTS;

	public:

		/**
		 * Creates a new Energizer instance.
		 * @param p_x the x-coordinate
		 * @param p_y the y-coordinate
		 * @param p_maze the Maze the Energyzer is on
		 * @param p_imageId the path to the Energyzer image
		 */
		Energizer(qreal p_x, qreal p_y, Maze* p_maze, const QString& p_imageId);

		/**
		 * Deletes the Energizer instance.
		 */
		~Energizer();

		/**
		 * Gets the type of the Energyzer.
		 * @return the type of the Energyzer
		 */
		QString getType();

		/**
		 * Computes an action on a collision with the Kapman.
		 * @param p_kapman the instance of Kapman which collides with the Energyzer
		 */
		void doActionOnCollision(Kapman* p_kapman);
};

#endif

