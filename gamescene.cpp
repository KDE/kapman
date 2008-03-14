/*
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

#include "gamescene.h"
#include <KStandardDirs>
#include <KLocalizedString>
#include "cell.h"
#include "bonus.h"

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

	QString lives("Lives : ");
	lives += QString::number((double)m_game->getLives());
	//Create the 'Lives' label
	m_livesLabel = new QGraphicsTextItem( ki18n(lives.toAscii().data()).toString() );
	m_livesLabel->setFont( QFont("Helvetica", 15, QFont::Bold, false) );
	m_livesLabel->setDefaultTextColor( QColor("#FFFFFF") );

	// Level label
	m_levelLabel = new QGraphicsTextItem(ki18nc("The current level", "Level : ").toString());
	m_levelLabel->setFont(QFont("Helvetica", 15, QFont::Bold, false));
	m_levelLabel->setDefaultTextColor(QColor("#FFFFFF"));
	
	// Add all the items
	// Maze
	m_mazeItem = new MazeItem(KStandardDirs::locate("appdata", "kapmanMaze.svg"));
	addItem(m_mazeItem);
	m_mazeItem->setZValue(-1);
	
	// Items
	m_elementItemList = new ElementItem ** [p_game->getMaze()->getNbRows()];
	for(int i = 0; i < p_game->getMaze()->getNbRows(); i++) {
		m_elementItemList[i] = new ElementItem * [p_game->getMaze()->getNbColumns()];
	}
	initItems();
	
	// Kapman
	m_kapmanItem = new KapmanItem(p_game->getKapman(), KStandardDirs::locate("appdata", "kapmanAnimTest.svg"));
	addItem(m_kapmanItem);
	m_kapmanItem->setZValue(1);
	
	// Ghosts
	for(int i=0; i<p_game->getGhostList().size(); i++) {
		Ghost* ghostModel = p_game->getGhostList().at(i);
		m_ghostItemList.append(new GhostItem(ghostModel, KStandardDirs::locate("appdata", ghostModel->getImageURL())));
		addItem(m_ghostItemList[i]);
		m_ghostItemList[i]->setZValue(1);
		// Connect each item and its model to manage state changes
		connect(ghostModel, SIGNAL(stateChanged(Ghost::GhostState)),m_ghostItemList[i] , SLOT(updateState(Ghost::GhostState)));
	}
	
	// Start labels
	addItem(m_introLabel);
	m_introLabel->setPos(this->width()/2 - m_introLabel->boundingRect().width()/2, this->height()/2 - m_introLabel->boundingRect().height()/2);
	// Ensure that the Label will overcome all items
	m_introLabel->setZValue(2);
		
	addItem(m_introLabel2);
	m_introLabel2->setPos(this->width()/2 - m_introLabel2->boundingRect().width()/2, this->height()/2 - m_introLabel2->boundingRect().height()/2 + m_introLabel->boundingRect().height()/2);
	// Ensure that the Label will overcome all items
	m_introLabel2->setZValue(2);
	
	//Score
	addItem(m_scoreLabel);
	m_scoreLabel->setPos(Cell::SIZE, this->height() + Cell::SIZE);
	// Ensure that the Label will overcome all items
	m_scoreLabel->setZValue(2);
		
	//Lives
	addItem(m_livesLabel);
	m_livesLabel->setPos(this->width() -m_livesLabel->boundingRect().width() , this->height() - Cell::SIZE- m_livesLabel->boundingRect().height()/2);
	// Ensure that the Label will overcome all items
	m_livesLabel->setZValue(3);

	// Level
	addItem(m_levelLabel);
	m_levelLabel->setPos((this->width() - m_levelLabel->boundingRect().width()) / 2 , this->height() - Cell::SIZE- m_levelLabel->boundingRect().height()/2);
	// Ensure that the Label will overcome all items
	m_levelLabel->setZValue(3);

	// Init the score, lives and level labels
	updateInfos();

	// Connect managePause signal to the scene
	connect(p_game, SIGNAL(managePause(bool)), this, SLOT(managePause(bool)));
	//Connect removeIntro signal to the scene
	connect(p_game, SIGNAL(removeIntro()), this, SLOT(removeIntro()));
	// Connect killElement signal to the scene
	connect(p_game, SIGNAL(sKillElement(qreal, qreal)), this, SLOT(killElement(qreal, qreal)));
	// Connect displayBonus signal to the scene
	connect(p_game, SIGNAL(sDisplayBonus()), this, SLOT(displayBonus()));	
	// Connect killBonus signal to the scene
	connect(p_game, SIGNAL(sKillBonus()), this, SLOT(killBonus()));
	// Connect disableDisplayBonus signal to the scene
	connect(p_game, SIGNAL(sDisableDisplayBonus()), this, SLOT(killBonus()));
	// Connect the kapman to the "updateInfos()" slot
	connect(p_game, SIGNAL(updatingInfos()), this, SLOT(updateInfos()));
	// Reinit the items on level completed
	connect(p_game, SIGNAL(leveled()), this, SLOT(initItems()));

}

GameScene::~GameScene() {
	delete m_game;
	delete m_pauseLabel;
	delete m_introLabel;
	delete m_introLabel2;
	delete m_scoreLabel;
	delete m_livesLabel;
	delete m_levelLabel;
	delete m_mazeItem;
	delete m_kapmanItem;
	for (int i = 0; i < m_ghostItemList.size(); i++) {
		delete m_ghostItemList[i];
	}
	for (int i = 0; i < m_game->getMaze()->getNbRows();i++) {
		for (int j = 0; j < m_game->getMaze()->getNbColumns(); j++) {
			delete m_elementItemList[i][j];
		}
		delete[] m_elementItemList[i];
	}
	delete[] m_elementItemList;
}

void GameScene::updateInfos() {
	QString lives("Lives : ");
	lives += QString::number((int)m_game->getLives());
	m_livesLabel->setPlainText(lives);

	QString score("Score : ");
	score += QString::number((double)m_game->getScore());
	m_scoreLabel->setPlainText(score);

	QString level("Level : ");
	level += QString::number((int)m_game->getLevel());
	m_levelLabel->setPlainText(level);
}


Game* GameScene::getGame() const {
	return m_game;
}

void GameScene::initItems() {
	QString itemImage;

	for(int i=0; i<m_game->getMaze()->getNbRows(); i++) {
		for(int j=0; j<m_game->getMaze()->getNbColumns(); j++) {
			if(m_game->getMaze()->getCell(i,j).getElement() != NULL){
				QString itemType = m_game->getMaze()->getCell(i,j).getElement()->getImageUrl();
				m_elementItemList[i][j] = new ElementItem(m_game->getMaze()->getCell(i,j).getElement(), KStandardDirs::locate("appdata", itemType));
				addItem(m_elementItemList[i][j]);
			}
		}
	}
}

void GameScene::managePause(bool p_pauseGame) {
	// If the label is not displayed yet, display it
	if(p_pauseGame) {
		addItem(m_pauseLabel);
		m_pauseLabel->setPos(this->width()/2 - m_pauseLabel->boundingRect().width()/2, this->height()/2 - m_pauseLabel->boundingRect().height()/2);
		// Ensure that the Label will overcome all items
		m_pauseLabel->setZValue(2);
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

void GameScene::displayBonus() {
	m_bonus = new ElementItem(m_game->getBonus(), KStandardDirs::locate("appdata", m_game->getBonus()->getImageUrl()));
	addItem(m_bonus);
}

void GameScene::killBonus() {
	if(items().contains(m_bonus))
		removeItem(m_bonus);
}
