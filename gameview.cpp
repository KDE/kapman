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

#include "gameview.h"
#include "gamescene.h"

GameView::GameView(Game * p_game) : QGraphicsView(new GameScene(p_game)) {
	setFocusPolicy(Qt::StrongFocus);
	// Forward the key press events to the Game instance
	connect(this, SIGNAL(keyPressed(QKeyEvent*)), p_game, SLOT(keyPressEvent(QKeyEvent*)));
}

GameView::~GameView() {

}

void GameView::resizeEvent(QResizeEvent* p_event) {
	fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void GameView::focusOutEvent(QFocusEvent* p_event) {
	// Pause the game if it is not already paused
	if (((GameScene*)scene())->getGame()->getTimer()->isActive()) {
		((GameScene*)scene())->getGame()->switchPause();
	}
}

void GameView::keyPressEvent(QKeyEvent* p_event) {
	emit(keyPressed(p_event));
}

