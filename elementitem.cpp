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

#include "elementitem.h"

ElementItem::ElementItem(Element* p_model, const QString & p_imagePath) : QGraphicsSvgItem(p_imagePath) {
	m_model = p_model;
	// Init the view coordinates
	setPos(p_model->getX() - boundingRect().width() / 2, p_model->getY() - boundingRect().height() / 2);
	// Connects the model to the view
	connect(p_model, SIGNAL(moved(qreal, qreal)), this, SLOT(update(qreal, qreal)));
	setCacheMode(DeviceCoordinateCache);
	setMaximumCacheSize(QSize(500, 500));
}

ElementItem::~ElementItem() {
	delete m_model;

}

Element* ElementItem::getModel() const {
	return m_model;
}

QPainterPath ElementItem::shape() const {
	QPainterPath path;
	path.addEllipse(boundingRect());
	return path;
}

void ElementItem::update(qreal p_x, qreal p_y) {
	// Compute the top-right coordinates of the item
	qreal x = p_x - boundingRect().width() / 2;
	qreal y = p_y - boundingRect().height() / 2;

	// Updates the view coordinates
	setPos(x, y);
}
