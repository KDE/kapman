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
#include <KDebug>
#include "gameview.h"
#include "gamescene.h"

GameView::GameView(Game * p_game) : QGraphicsView(new GameScene(p_game)) {
	m_size = size();
}

GameView::~GameView() {

}

void GameView::resizeManager() {
	// Resize the scene to fit in the viewport
	//will be replaced when the resizeScene procedure will be implemented
	fitInView(sceneRect(), Qt::KeepAspectRatio);
	((GameScene*)scene())->resizeScene(size());
}

void GameView::keyPressEvent(QKeyEvent* p_event) {
	emit(keyPressed(p_event));
}
