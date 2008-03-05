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

#ifndef __ENERGIZER_H
#define __ENERGIZER_H

#include <QObject>
#include "element.h"

/**
 * This class represents a energizer of the Kapman maze
 */
class Energizer : public Element {

	Q_OBJECT

	public:

		/** The pill's points */
		static const int POINTS;


	public:

		/**
		 * Creates a new Energizer instance
		 */
		Energizer(qreal p_x, qreal p_y, Maze* p_maze, const QString& p_imageUrl);

		/**
		 * Deletes the Energizer instance
		 */
		~Energizer();

		/**
		 * @return the type of the Element
		 */
		QString getType();

		/**
		 * Computes an action on a collision with the kapman
		 * @param p_element the kapman that collides with this element
		 */
		void doActionOnCollision(Kapman* p_kapman);

	signals:

		/**
		 * Emitted when the energyzer is eaten
		 */
		//void energyzerEaten();
};

#endif
