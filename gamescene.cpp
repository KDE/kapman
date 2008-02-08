/**
 * Copyright 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>
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

#include <KStandardDirs>
#include <KLocalizedString>
#include "cell.h"
#include "gamescene.h"
#include "mazeitem.h"
#include "characteritem.h"
#include "kapmanitem.h"

GameScene::GameScene(Game * p_game) : m_game(p_game) {
	// Create the 'PAUSE' label
	m_pauseLabel = new QGraphicsTextItem( ki18n("PAUSED").toString() );
	m_pauseLabel->setFont( QFont("Helvetica", 35, QFont::Bold, false) );
	m_pauseLabel->setDefaultTextColor( QColor("#FFFF00") );

	// Create the 'INTRO' label
	m_introLabel = new QGraphicsTextItem( ki18n("GET READY !!!").toString() );
	m_introLabel->setFont( QFont("Helvetica", 25, QFont::Bold, false) );
	m_introLabel->setDefaultTextColor( QColor("#FFFF00") );
	
	m_introLabel2 = new QGraphicsTextItem( ki18n("Press any key to start").toString() );
	m_introLabel2->setFont( QFont("Helvetica", 15, QFont::Bold, false) );
	m_introLabel2->setDefaultTextColor( QColor("#FF0000") );

	//Create the 'Score' label

	m_scoreLabel = new QGraphicsTextItem( ki18n("Score : ").toString() );
	m_scoreLabel->setFont( QFont("Helvetica", 15, QFont::Bold, false) );
	m_scoreLabel->setDefaultTextColor( QColor("#FFFFFF") );

	QString lifes("Lifes : ");
		lifes += QString::number((double)m_game->getLifes());
	//Create the 'Lifes' label
	m_lifesLabel = new QGraphicsTextItem( ki18n(lifes.toAscii().data()).toString() );
	m_lifesLabel->setFont( QFont("Helvetica", 15, QFont::Bold, false) );
	m_lifesLabel->setDefaultTextColor( QColor("#FFFFFF") );
	
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
	addItem(m_introLabel);
		m_introLabel->setPos(this->width()/2 - m_introLabel->boundingRect().width()/2, this->height()/2 - m_introLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		m_introLabel->setZValue(2.0);
		
	addItem(m_introLabel2);
		m_introLabel2->setPos(this->width()/2 - m_introLabel2->boundingRect().width()/2, this->height()/2 - m_introLabel2->boundingRect().height()/2 + m_introLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		m_introLabel2->setZValue(2.0);
	

	//Score
	addItem(m_scoreLabel);
		m_scoreLabel->setPos(Cell::SIZE, this->height() + Cell::SIZE);
		// Ensure that the Label will overcome all items
		m_scoreLabel->setZValue(2.0);
	//Lifes
	addItem(m_lifesLabel);
		m_lifesLabel->setPos(this->width() -m_lifesLabel->boundingRect().width() , this->height() - Cell::SIZE- m_scoreLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		m_lifesLabel->setZValue(3.0);


	// Connect managePause signal to the scene
	connect(p_game, SIGNAL(managePause(bool)), this, SLOT(managePause(bool)));
	
	//Connect removeIntro signal to the scene
	connect(p_game, SIGNAL(removeIntro()), this, SLOT(removeIntro()));
	
	// Connects killElement signal to the scene
	connect(p_game, SIGNAL(sKillElement(qreal, qreal)), this, SLOT(killElement(qreal, qreal)));	

	// Connects the kapman to the "updateInfos()" slot
	connect(p_game, SIGNAL(updatingInfos()), this, SLOT(updateInfos()));	

}

GameScene::~GameScene() {
	delete m_game;
	delete m_pauseLabel;
	delete m_introLabel;
	delete m_introLabel2;
}


	

void GameScene::updateInfos() {
	QString lifes("Lifes : ");
		lifes += QString::number((double)m_game->getLifes());
	m_lifesLabel->setPlainText(lifes);

	QString score("Score : ");
		score += QString::number((double)m_game->getScore());
	m_scoreLabel->setPlainText(score);
}


Game* GameScene::getGame() const {
	return m_game;
}

void GameScene::managePause(bool pauseGame) {
	// If the label is not displayed yet, display it
	if(pauseGame) {
		addItem(m_pauseLabel);
		m_pauseLabel->setPos(this->width()/2 - m_pauseLabel->boundingRect().width()/2, this->height()/2 - m_pauseLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		m_pauseLabel->setZValue(2.0);
	}
	else {
	// If the label is displayed, remove it
		if(items().contains(m_pauseLabel)) {
			removeItem(m_pauseLabel);
		}
	}
}

void GameScene::removeIntro() {
	//If the Intro Label is displayed, remove it
	if(items().contains(m_introLabel)) {
		removeItem(m_introLabel);
		removeItem(m_introLabel2);
	}
}

void GameScene::killElement(qreal p_x, qreal p_y) {
	int x, y;
	x = (int)((p_x - (Cell::SIZE * 0.5))/Cell::SIZE);
	y = (int)((p_y - (Cell::SIZE * 0.5))/Cell::SIZE);
	removeItem(m_elementItemList[y][x]);
	m_elementItemList[y][x] = NULL;
}
