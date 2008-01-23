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

#ifndef __CHARACTERITEM_H
#define __CHARACTERITEM_H

#include <QGraphicsSvgItem>
#include <QString>
#include "character.h"

/**
 * This class is the graphical representation of a character
 */
class CharacterItem : public QGraphicsSvgItem {

	Q_OBJECT
	
	private:
	
		/** pointer on the model */
		Character * m_model;

	public:

		/**
		 * Creates a new CharacterItem instance
		 * @param p_model the character model
		 * @param p_imagePath the character image path
		 */
		CharacterItem(Character* p_model, QString p_imagePath);

		/**
		 * Deletes the CharacterItem instance
		 */
		~CharacterItem();
		
		/**
		 * @return the model
		 */
		Character* getModel() const;

	public slots:

		/**
		 * Updates the view coordinates
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		virtual void update(qreal p_x, qreal p_y);
};

#endif
