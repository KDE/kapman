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
#include <KLocalizedString>
#include "gamescene.h"
#include "mazeitem.h"
#include "kapmanitem.h"
#include "ghostitem.h"

GameScene::GameScene(Game * p_game) {
	// Create the 'PAUSE' label
	pauseLabel = new QGraphicsTextItem( ki18n("PAUSE").toString() );
	pauseLabel->setFont( QFont("Helvetica", 35, QFont::Bold, false) );
	
	pauseLabel->setDefaultTextColor( QColor("#FFFF00") );

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
	
	// Connect managePause signal to the scene
	connect(p_game, SIGNAL(managePause(bool)), this, SLOT(managePause(bool)));
}

GameScene::~GameScene() {

}

void GameScene::managePause(bool pauseGame) {
	// If the label is not displayed yet, display it
	if(pauseGame) {
		addItem(pauseLabel);
		pauseLabel->setPos(this->width()/2 - pauseLabel->boundingRect().width()/2, this->height()/2 - pauseLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		pauseLabel->setZValue(2.0);
	}
	else {
	// If the label is displayed, remove it
		removeItem(pauseLabel);
	}
}
