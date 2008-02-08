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

#ifndef _KAPMAN_ITEM_H
#define _KAPMAN_ITEM_H

#include "characteritem.h"
#include "kapman.h"

/**
 * This class manage the display of the kapman
 */
class KapmanItem : public CharacterItem {

	Q_OBJECT

	public:
		/**
		 * Creates a new KapmanItem instance
		 * @param p_model the kapman model
		 * @param p_imagePath the kapman image path
		 */
		KapmanItem(Kapman* p_model, QString p_imagePath);

		/**
		 * Deletes the KapmanItem instance
		 */
		~KapmanItem();


	public slots:

		/**
		 * Manages the colllisions between kapman and the other elements
		 */
		void manageCollision();
};

#endif
