/*
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

#ifndef __CHARACTERITEM_H
#define __CHARACTERITEM_H

#include "elementitem.h"
#include "character.h"

#include <QTimer>

/**
 * @brief This class is the graphical representation of a Character.
 */
class CharacterItem : public ElementItem {

	Q_OBJECT

	protected:

		/** Timer used to make the character blink */
		QTimer* m_blinkTimer;

		/** Number of ticks of the blink timer */
		int m_nbBlinks;

	public:

		/**
		 * Creates a new CharacterItem instance.
		 * @param p_model the Character model
		 */
		CharacterItem(Character* p_model);

		/**
		 * Deletes the CharacterItem instance.
		 */
		~CharacterItem();
		
	public slots:

		/**
		 * Updates the CharacterItem coordinates.
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		virtual void update(qreal p_x, qreal p_y);
	
		/**
		 * Starts the character blinking.
		 */
		virtual void startBlinking();

		/**
		 * Makes the character blink.
		 */
		virtual void blink();
};

#endif

