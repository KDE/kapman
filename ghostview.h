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

#ifndef __GHOSTVIEW_H
#define __GHOSTVIEW_H

#include <QGraphicsSvgItem>
#include <QString>
#include "ghost.h"

/**
 * This class is the graphical representation of the main character
 */
class GhostView : public QGraphicsSvgItem {

	Q_OBJECT

	public:

		/**
		 * Creates a new GhostView instance
		 * @param p_model the Ghost
		 */
		GhostView(Ghost* p_model, QString p_imagePath);

		/**
		 * Deletes the GhostView instance
		 */
		~GhostView();

	signals:

		/**
		 * Warns the Ghost model that his coordinates have to be changed
		 * Emitted when the Ghost reaches a border of the maze
		 * @param p_newX the new (or unchanged) X coordinate
		 * @param p_newY the new (or unchanged) Y coordinate
		 */
		void borderReached(qreal p_newX, qreal p_newY);

	public slots:

		/**
		 * Updates the view coordinates
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void update(qreal p_x, qreal p_y);
};

#endif
