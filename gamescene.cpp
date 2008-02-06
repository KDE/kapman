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
#include "cell.h"
#include "gamescene.h"
#include "mazeitem.h"
#include "characteritem.h"
#include "kapmanitem.h"

GameScene::GameScene(Game * p_game) : m_game(p_game) {
	// Create the 'PAUSE' label
	pauseLabel = new QGraphicsTextItem( ki18n("PAUSED").toString() );
	pauseLabel->setFont( QFont("Helvetica", 35, QFont::Bold, false) );
	pauseLabel->setDefaultTextColor( QColor("#FFFF00") );

	// Create the 'INTRO' label
	introLabel = new QGraphicsTextItem( ki18n("GET READY !!!").toString() );
	introLabel->setFont( QFont("Helvetica", 25, QFont::Bold, false) );
	introLabel->setDefaultTextColor( QColor("#FFFF00") );
	
	introLabel2 = new QGraphicsTextItem( ki18n("Press any key to start").toString() );
	introLabel2->setFont( QFont("Helvetica", 15, QFont::Bold, false) );
	introLabel2->setDefaultTextColor( QColor("#FF0000") );

	// Add all the items
	// Maze
	MazeItem* mazeItem = new MazeItem(KStandardDirs::locate("appdata", "kapmanMaze.svg"));
	addItem(mazeItem);
	mazeItem->setZValue(-1);
	
	m_elementItemList = new ElementItem ** [p_game->getMaze()->getNbRows()];
	for(int i = 0; i < p_game->getMaze()->getNbRows(); i++) {
		m_elementItemList[i] = new ElementItem * [p_game->getMaze()->getNbColumns()];
	}
	
	// Items
	for(int i=0; i<p_game->getMaze()->getNbRows(); i++) {
		for(int j=0; j<p_game->getMaze()->getNbColumns(); j++) {
			if(p_game->getMaze()->getCell(i,j).getElement() != NULL){
				QString itemType = p_game->getMaze()->getCell(i,j).getElement()->getImageUrl();
				m_elementItemList[i][j] = new ElementItem(p_game->getMaze()->getCell(i,j).getElement(),KStandardDirs::locate("appdata", itemType));
				addItem(m_elementItemList[i][j]);
			}
		}
	}
	// Kapman
	addItem(new KapmanItem(p_game->getKapman(), KStandardDirs::locate("appdata", "kapman_test.svg")));
	// Ghosts
	for(int i=0; i<p_game->getGhostList().size(); i++) {
		addItem(new CharacterItem(p_game->getGhostList().at(i), 
			KStandardDirs::locate("appdata", p_game->getGhostList().at(i)->getImageURL())));
	}
	// Start labels
	addItem(introLabel);
		introLabel->setPos(this->width()/2 - introLabel->boundingRect().width()/2, this->height()/2 - introLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		introLabel->setZValue(2.0);
		
	addItem(introLabel2);
		introLabel2->setPos(this->width()/2 - introLabel2->boundingRect().width()/2, this->height()/2 - introLabel2->boundingRect().height()/2 + introLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		introLabel2->setZValue(2.0);
	
	// Connect managePause signal to the scene
	connect(p_game, SIGNAL(managePause(bool)), this, SLOT(managePause(bool)));
	
	//Connect removeIntro signal to the scene
	connect(p_game, SIGNAL(removeIntro()), this, SLOT(removeIntro()));
	
	// Connects killElement signal to the scene
	connect(p_game, SIGNAL(sKillElement(qreal, qreal)), this, SLOT(killElement(qreal, qreal)));	
}

GameScene::~GameScene() {

}

Game* GameScene::getGame() const {
	return m_game;
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
		if(items().contains(pauseLabel)) {
			removeItem(pauseLabel);
		}
	}
}

void GameScene::removeIntro() {
	//If the Intro Label is displayed, remove it
	if(items().contains(introLabel)) {
		removeItem(introLabel);
		removeItem(introLabel2);
	}
}

void GameScene::killElement(qreal p_x, qreal p_y) {
	int x, y;
	x = (int)((p_x - (Cell::SIZE * 0.5))/Cell::SIZE);
	y = (int)((p_y - (Cell::SIZE * 0.5))/Cell::SIZE);
	removeItem(m_elementItemList[y][x]);
	m_elementItemList[y][x] = NULL;
}
