/**
 * Copyright 2007-2008 Nathalie Liesse <nathalie.liesse@gmail.com>
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

#include <QGraphicsScene>
#include "characteritem.h"
#include "kapmanitem.h"
#include "ghost.h"

KapmanItem::KapmanItem(Kapman* p_model, QString p_imagePath) :	CharacterItem(p_model, p_imagePath) {
	connect(p_model, SIGNAL(gameUpdated()), this, SLOT(manageCollision()));
}

KapmanItem::~KapmanItem() {

}

void KapmanItem::manageCollision() {
	QList<QGraphicsItem *> collidingList = collidingItems();

	// The signal is emitted only if the list contains more than 1 items (to exclude the case
	// when the kapman only collides with the maze)
	if(collidingList.size() > 1) {
		for(int i = 0 ; i < collidingList.size() ; i++) {
			// The maze has a negative zValue which allows to exclude it from the treatment of collisions
			if (collidingList[i]->zValue() >= 0) {
				((ElementItem*)collidingList[i])->getModel()->doActionOnCollision((Kapman*)getModel());
			}
		}
	}
}
