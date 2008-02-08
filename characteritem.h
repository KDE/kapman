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

#ifndef __CHARACTERITEM_H
#define __CHARACTERITEM_H

#include "elementitem.h"
#include "character.h"

/**
 * This class is the graphical representation of a character
 */
class CharacterItem : public ElementItem {

	Q_OBJECT

	public:

		/**
		 * Creates a new CharacterItem instance
		 * @param p_model the character model
		 * @param p_imagePath the character image path
		 */
		CharacterItem(Character* p_model, QString & p_imagePath);

		/**
		 * Deletes the CharacterItem instance
		 */
		~CharacterItem();
};

#endif
