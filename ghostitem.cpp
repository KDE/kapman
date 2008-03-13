/*
 * Copyright 2007-2008 Pierre-Benoit Besse <besse.pb@gmail.com>
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

#include "ghostitem.h"

GhostItem::GhostItem(Ghost* p_model, const QString & p_imagePath) : CharacterItem (p_model, p_imagePath) {
	
}

GhostItem::~GhostItem() {
	
}

void GhostItem::update(qreal p_x, qreal p_y) {
	// Compute the top-right coordinates of the item
	qreal x = p_x - boundingRect().width() / 2;
	qreal y = p_y - boundingRect().height() / 2;

	// Updates the view coordinates
	setPos(x, y);
}

void GhostItem::updateState(Ghost::GhostState p_state) {
	if( ((Ghost*)getModel())->getState() == Ghost::HUNTER) {
		setElementId("ghost_hunter");
	}
	else if(((Ghost*)getModel())->getState() == Ghost::WHITE_PREY) {
		setElementId("ghost_prey_white");
	}
	else {
		setElementId("ghost_prey");
	}
}
