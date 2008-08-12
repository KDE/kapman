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

#ifndef __ELEMENTITEM_H
#define __ELEMENTITEM_H

#include <QGraphicsSvgItem>

#include "element.h"

/**
 * @brief This class is the graphical representation of a game Element.
 */
class ElementItem : public QGraphicsSvgItem {

	Q_OBJECT

	private:
		/** The Label containing the points won when eaten, to display on the scene */
		QGraphicsTextItem* m_pointsToDisplay;
	
	protected:
	
		/** The instance of Element the ElementItem will represent */
		Element* m_model;

	public:

		/**
		 * Creates a new ElementItem instance.
		 * @param p_model the Element model
		 * @param p_imagePath the Element image path
		 */
		ElementItem(Element* p_model, const QString & p_imagePath);

		/**
		 * Deletes the ElementItem instance.
		 */
		~ElementItem();
		
		/**
		 * Gets the Element model.
		 * @return the model
		 */
		Element* getModel() const;

		/**
		 * Reimplement QGraphicsItem::shape() to return an ellipse to improve collisions.
		 */
		QPainterPath shape() const;

	public slots:

		/**
		 * Updates the ElementItem coordinates.
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		virtual void update(qreal p_x, qreal p_y);
};

#endif

