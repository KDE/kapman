/* This file is part of Kapman.
   Created by Nathalie Liesse <nathalie.liesse@gmail.com>

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
#include "characteritem.h"
#include "kapmanitem.h"
#include "ghost.h"

KapmanItem::KapmanItem(Kapman* p_model, QString p_imagePath) :	CharacterItem(p_model, p_imagePath) {
}

KapmanItem::~KapmanItem() {

}

void KapmanItem::update(qreal p_x, qreal p_y) {
	// Compute the top-right coordinates of the item
	qreal x = p_x - boundingRect().width() / 2;
	qreal y = p_y - boundingRect().height() / 2;

	// Updates the view coordinates
	setPos(x, y);

	QList<QGraphicsItem *> collidingList = collidingItems();

	// The signal is emitted only if the list contains more than 1 items (to exclude the case
	// when the kapman only collides with the maze
	if(collidingList.size() > 1) {
// 		QList<QGraphicsItem *>::iterator i;
// 		for(i = collidingList.begin() ; i < collidingList.end() ; i++) {
// 			if ((*i)->zValue() >= 0) {
// 				((Ghost*)((CharacterItem*)(*i))->getModel())->doActionOnCollision((Kapman*)getModel());
// 			}
// 		}
		for(int i = 0 ; i < collidingList.size() ; i++) {
			if (collidingList[i]->zValue() >= 0) {
				((Ghost*)((CharacterItem*)collidingList[i])->getModel())->doActionOnCollision((Kapman*)getModel());
			}
		}
	}
}
