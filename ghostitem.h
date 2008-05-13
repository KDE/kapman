/*
 * Copyright 2007-2008 Pierre-Benoit Besse <besse.pb@gmail.com>
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

#ifndef __GHOSTITEM_H
#define __GHOSTITEM_H

#include "characteritem.h"
#include "ghost.h"

/**
 * This class is the graphical representation of a ghost
 */
class GhostItem : public CharacterItem {

	Q_OBJECT

	private:

		/** Timer to start blinking */
		QTimer* m_startBlinkingTimer;

	public:

		/**
		 * Creates a new GhostItem instance
		 * @param p_model the ghost model
		 * @param p_imagePath the ghost image path
		 */
		GhostItem(Ghost* p_model, const QString & p_imagePath);

		/**
		 * Deletes the CharacterItem instance
		 */
		~GhostItem();
		
	public slots:

		/**
		 * Updates the view coordinates
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void update(qreal p_x, qreal p_y);
		
		/**
		 * Update the ghostItem image with its model's state
		 */
		void updateState();

		/**
		 * Implements the CharacterItem method
		 */
		void blink();
};

#endif
