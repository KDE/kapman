/* This file is part of Kapman.
   Created by Alexandre GALINIER <alex.galinier@hotmail.com>

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

#include <KStandardDirs>
#include "gamescene.h"
#include "mazeitem.h"
#include "kapmanitem.h"
#include "ghostitem.h"

GameScene::GameScene(Game * p_game) {
	// Add all the items
	addItem(new MazeItem(
		KStandardDirs::locate("appdata", "kapmanMaze.svg")));
	addItem(new KapmanItem(p_game->getKapman(),
		KStandardDirs::locate("appdata", "kapman_test.svg")));
	for(int i=0; i<p_game->getGhostList().size(); i++) {
		addItem(new GhostItem(p_game->getGhostList().at(i),
			KStandardDirs::locate("appdata",
			p_game->getGhostList().at(i)->getImageURL())));
	}
}

GameScene::~GameScene() {

}
