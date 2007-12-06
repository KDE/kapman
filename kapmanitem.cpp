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
	setPos(p_model->getX(), p_model->getY());
	// Connects the model to the view
	connect(p_model, SIGNAL(moved(qreal, qreal)), this, SLOT(update(qreal, qreal)));

	// Connects the view to the model to make the kapman change side on the maze when reaching a border
	connect(this, SIGNAL(borderReached(qreal, qreal)), p_model, SLOT(changeMazeSide(qreal, qreal)));
}

KapmanItem::~KapmanItem() {

}

void KapmanItem::update(qreal p_x, qreal p_y) {
	// If the Kapman reaches a border, he has to "circle around" the maze and continu his way from the other side
	// When this is done, a signal warns the kapman model that his coordinates have changed
	// West side test
	if(p_x <= 0) {
		// 
		p_x += scene()->itemsBoundingRect().width() - this->boundingRect().width();
		emit(borderReached(p_x, p_y));
	}
	// East side test
	else if(p_x > (scene()->itemsBoundingRect().width() - this->boundingRect().width())) {
		p_x = 1;
		emit(borderReached(p_x, p_y));
	}
	// North side test
	else if(p_y <= 0) {
		p_y += scene()->itemsBoundingRect().height() - this->boundingRect().height();
		emit(borderReached(p_x, p_y));
	}
	// South side test
	else if(p_y > (scene()->itemsBoundingRect().height() - this->boundingRect().height())) {
		p_y = 1;
		emit(borderReached(p_x, p_y));
	}

	// Updates the view coordinates
	setPos(p_x, p_y);
}
