/* This file is part of Kapman.
   Created by Thomas Gallinari <tg8187@yahoo.fr>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,m
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
*/

#include "gameview.h"
#include "gamescene.h"

GameView::GameView(Game * p_game) : QGraphicsView(new GameScene(p_game)) {
	// Connect the key events to the game manager
	connect(this, SIGNAL(keyPressed(QKeyEvent*)),
			p_game, SLOT(keyPressEvent(QKeyEvent*)));
}

GameView::~GameView() {

}

void GameView::resizeManager() {
	// Resize the scene to fit in the viewport
	// TODO replace with the resizeScene() method
	fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void GameView::keyPressEvent(QKeyEvent* p_event) {
	emit(keyPressed(p_event));
}
