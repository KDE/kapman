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
#include <QGraphicsScene>

#include "kapmanitem.h"

KapmanItem::KapmanItem(Kapman* p_model, QString p_imagePath) :
		QGraphicsSvgItem(p_imagePath) {
	// Init the view coordinates
	setPos(p_model->getX() - boundingRect().width() / 2,
		   p_model->getY() - boundingRect().height() / 2);
	// Connects the model to the view
	connect(p_model, SIGNAL(moved(qreal, qreal)), this, SLOT(update(qreal, qreal)));

	// Connects the view to the model to make the kapman change side on the maze when reaching a border
	// TODO re-develop it according to new architecture
	//connect(this, SIGNAL(borderReached(qreal, qreal)), p_model, SLOT(changeMazeSide(qreal, qreal)));
}

KapmanItem::~KapmanItem() {

}

void KapmanItem::update(qreal p_x, qreal p_y) {
	// Compute the top-right coordinates of the item
	qreal x = p_x - boundingRect().width() / 2;
	qreal y = p_y - boundingRect().height() / 2;
	// If the Kapman reaches a border, he has to "circle around" the maze and
	// continu his way from the other side
	// When this is done, a signal warns the kapman model that his coordinates have changed
	// TODO re-develop it according to new architecture
	// West side test
// 	if(x <= 0) {
// 		// 
// 		x += scene()->itemsBoundingRect().width() -
// 				this->boundingRect().width();
// 		emit(borderReached(x, y));
// 	}
// 	// East side test
// 	else if(x > (scene()->itemsBoundingRect().width() -
// 					this->boundingRect().width())) {
// 		x = 1;
// 		emit(borderReached(x, y));
// 	}
// 	// North side test
// 	else if(y <= 0) {
// 		y += scene()->itemsBoundingRect().height() -
// 				this->boundingRect().height();
// 		emit(borderReached(x, y));
// 	}
// 	// South side test
// 	else if(y > (scene()->itemsBoundingRect().height() -
// 					this->boundingRect().height())) {
// 		y = 1;
// 		emit(borderReached(x, y));
// 	}

	// Updates the view coordinates
	setPos(x, y);
}
