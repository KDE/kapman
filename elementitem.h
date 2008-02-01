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

#ifndef __ELEMENTITEM_H
#define __ELEMENTITEM_H

#include <QGraphicsSvgItem>
#include "element.h"

/**
 * This class is the graphical representation of a game element
 */
class ElementItem : public QGraphicsSvgItem {

	Q_OBJECT
	
	protected:
	
		/** Pointer on the model */
		Element * m_model;

	public:

		/**
		 * Creates a new ElementItem instance
		 * @param p_model the element model
		 * @param p_imagePath the element image path
		 */
		ElementItem(Element* p_model, QString p_imagePath);

		/**
		 * Deletes the ElementItem instance
		 */
		~ElementItem();
		
		/**
		 * @return the model
		 */
		Element* getModel() const;

	public slots:

		/**
		 * Updates the view coordinates
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		virtual void update(qreal p_x, qreal p_y);
};

#endif
