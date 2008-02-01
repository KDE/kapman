/* This file is part of Kapman.
   Created by Gaël Courcelle & Allanic Alexia <tg8187@yahoo.fr>

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

#ifndef __ENERGIZER_H
#define __ENERGIZER_H
#include "element.h"
#include <QObject>

/**
 * This class represents a energizer of the Kapman maze
 */
class Energizer : public Element {

	public:

		/** The pill's points */
		static const qreal POINTS;


	public:

		/**
		 * Creates a new Energizer instance
		 */
		Energizer(qreal p_x, qreal p_y, Maze* p_maze, QString p_imageUrl);

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
};

#endif
