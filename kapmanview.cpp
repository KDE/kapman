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

#include "kapmanview.h"

KapmanView::KapmanView(Kapman* p_model, QString p_imagePath) :
		QGraphicsSvgItem(p_imagePath) {
	// Init the view coordinates
	setPos(p_model->getX(), p_model->getY());
	// Connect the model to the view
	connect(p_model, SIGNAL(moved(int, int)), this, SLOT(update(int, int)));
}

KapmanView::~KapmanView() {

}

void KapmanView::update(int p_x, int p_y) {
	// Update the view coordinates
	setPos(p_x, p_y);
}
