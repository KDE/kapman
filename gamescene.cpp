/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
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
#include "cell.h"
#include "bonus.h"

#include <QPixmapCache>
#include <KStandardDirs>
#include <KLocalizedString>

GameScene::GameScene(Game* p_game) : m_game(p_game) {
	connect(p_game, SIGNAL(levelStarted(bool)), SLOT(intro(bool)));
	connect(p_game, SIGNAL(gameStarted()), this, SLOT(start()));
	connect(p_game, SIGNAL(pauseChanged(bool, bool)), this, SLOT(setPaused(bool, bool)));
	connect(p_game, SIGNAL(elementEaten(qreal, qreal)), this, SLOT(hideElement(qreal, qreal)));
	connect(p_game, SIGNAL(bonusOn()), this, SLOT(displayBonus()));	
	connect(p_game, SIGNAL(bonusOff()), this, SLOT(hideBonus()));
	connect(p_game, SIGNAL(dataChanged(Game::InformationTypes)), this, SLOT(updateInfo(Game::InformationTypes)));

	// Set the pixmap cache limit to improve performance
	setItemIndexMethod(NoIndex);
	QPixmapCache::setCacheLimit(32768);

	// Create the MazeItem
	m_mazeItem = new MazeItem(KStandardDirs::locate("appdata", "maze.svg"));
	m_mazeItem->setZValue(-1);
	// Create the KapmanItem
	m_kapmanItem = new KapmanItem(p_game->getKapman(), KStandardDirs::locate("appdata", "kapman.svg"));
	m_kapmanItem->setZValue(1);
	// Create the GhostItems
	for (int i = 0; i < p_game->getGhosts().size(); i++) {
		m_ghostItems.append(new GhostItem(p_game->getGhosts()[i], KStandardDirs::locate("appdata", p_game->getGhosts()[i]->getImageURL())));
		m_ghostItems[i]->setZValue(1);
	}
	// Create the Pill and Energizer items
	m_elementItems = new ElementItem**[m_game->getMaze()->getNbRows()];
	for (int i = 0; i < m_game->getMaze()->getNbRows(); i++) {
		m_elementItems[i] = new ElementItem*[m_game->getMaze()->getNbColumns()];
		for (int j = 0; j < m_game->getMaze()->getNbColumns(); j++) {
			if (m_game->getMaze()->getCell(i, j).getElement() != NULL) {
				m_elementItems[i][j] = new ElementItem(m_game->getMaze()->getCell(i, j).getElement(),
						KStandardDirs::locate("appdata", m_game->getMaze()->getCell(i, j).getElement()->getImageUrl()));
			} else {
				m_elementItems[i][j] = NULL;
			}
		}
	}
	// Create the Bonus item
	m_bonusItem = new ElementItem(m_game->getBonus(), KStandardDirs::locate("appdata", "bonus.svg"));

	// Create the introduction labels
	m_introLabel = new QGraphicsTextItem(i18n("GET READY !!!"));
	m_introLabel->setFont(QFont("Helvetica", 25, QFont::Bold, false));
	m_introLabel->setDefaultTextColor(QColor("#FFFF00"));
	m_introLabel->setZValue(2);
	m_introLabel2 = new QGraphicsTextItem(i18n("Press any arrow key to start"));
	m_introLabel2->setFont(QFont("Helvetica", 15, QFont::Bold, false));
	m_introLabel2->setDefaultTextColor(QColor("#FFFF00"));
	m_introLabel2->setZValue(2);
	// Create the new level label
	m_newLevelLabel = new QGraphicsTextItem();
	m_newLevelLabel->setFont(QFont("Helvetica", 35, QFont::Bold, false));
	m_newLevelLabel->setDefaultTextColor(QColor("#FFFF00"));
	m_newLevelLabel->setZValue(2);
	// Create the score label
	m_scoreLabel = new QGraphicsTextItem();
	m_scoreLabel->setFont(QFont("Helvetica", 15, QFont::Bold, false));
	m_scoreLabel->setDefaultTextColor(QColor("#FFFFFF"));
	// Create the lives label
	m_livesLabel = new QGraphicsTextItem();
	m_livesLabel->setFont(QFont("Helvetica", 15, QFont::Bold, false));
	m_livesLabel->setDefaultTextColor(QColor("#FFFFFF"));
	// Create the level label
	m_levelLabel = new QGraphicsTextItem();
	m_levelLabel->setFont(QFont("Helvetica", 15, QFont::Bold, false));
	m_levelLabel->setDefaultTextColor(QColor("#FFFFFF"));
	// Create the pause label
	m_pauseLabel = new QGraphicsTextItem(i18n("PAUSED"));
	m_pauseLabel->setFont(QFont("Helvetica", 35, QFont::Bold, false));
	m_pauseLabel->setDefaultTextColor(QColor("#FFFF00"));

	// Display the MazeItem
	addItem(m_mazeItem);
	// Display the KapmanItem
	addItem(m_kapmanItem);
	// Display each GhostItem
	for (int i = 0; i < m_ghostItems.size(); i++) {
		addItem(m_ghostItems[i]);
	}
	// Display each Pill and Energizer item and introduction labels
	intro(true);
	// Initialize the information labels (score, lives and label)
	updateInfo(Game::AllInfo);
	// Display the score label
	addItem(m_scoreLabel);
	m_scoreLabel->setPos(Cell::SIZE, height() + Cell::SIZE);
	// Display the lives label
	addItem(m_livesLabel);
	m_livesLabel->setPos(width() - m_livesLabel->boundingRect().width() - 20 , height() - Cell::SIZE - m_livesLabel->boundingRect().height() / 2);
	// Display the level label
	addItem(m_levelLabel);
	m_levelLabel->setPos((width() - m_levelLabel->boundingRect().width()) / 2 , height() - Cell::SIZE - m_levelLabel->boundingRect().height() / 2);
}

GameScene::~GameScene() {
	delete m_game;
	delete m_mazeItem;
	delete m_kapmanItem;
	for (int i = 0; i < m_ghostItems.size(); i++) {
		delete m_ghostItems[i];
	}
	for (int i = 0; i < m_game->getMaze()->getNbRows();i++) {
		for (int j = 0; j < m_game->getMaze()->getNbColumns(); j++) {
			if (m_elementItems[i][j] != NULL) {
				delete m_elementItems[i][j];
			}
		}
		delete[] m_elementItems[i];
	}
	delete[] m_elementItems;
	delete m_bonusItem;
	delete m_introLabel;
	delete m_introLabel2;
	delete m_newLevelLabel;
	delete m_scoreLabel;
	delete m_livesLabel;
	delete m_levelLabel;
	delete m_pauseLabel;
}

Game* GameScene::getGame() const {
	return m_game;
}

void GameScene::intro(const bool p_newLevel) {
	// If a new level has begun
	if (p_newLevel) {
		// Set each Pill and Energizer item to its original coordinates
		for (int i = 0; i < m_game->getMaze()->getNbRows(); i++) {
			for (int j = 0; j < m_game->getMaze()->getNbColumns(); j++) {
				if (m_elementItems[i][j] != NULL) {
					if (!items().contains(m_elementItems[i][j])) {
						addItem(m_elementItems[i][j]);
					}
				}
			}
		}
		// Display the new level label
		m_newLevelLabel->setPlainText(i18n("Level %1",m_game->getLevel()));
		addItem(m_newLevelLabel);
		m_newLevelLabel->setPos((width() - m_newLevelLabel->boundingRect().width()) / 2, (height() - m_newLevelLabel->boundingRect().height()) / 2);
		// Display the introduction label
		if (!items().contains(m_introLabel2)) {
			addItem(m_introLabel2);
			m_introLabel2->setPos((width() - m_introLabel2->boundingRect().width()) / 2,
				(height() - m_introLabel2->boundingRect().height() + m_newLevelLabel->boundingRect().height()) / 2);
		}
	} else {
		// Display the introduction labels
		if (!items().contains(m_introLabel)) {
			addItem(m_introLabel);
			m_introLabel->setPos((width() - m_introLabel->boundingRect().width()) / 2, (height() - m_introLabel->boundingRect().height()) / 2);
		}
		if (!items().contains(m_introLabel2)) {
			addItem(m_introLabel2);
			m_introLabel2->setPos((width() - m_introLabel2->boundingRect().width()) / 2,
				(height() - m_introLabel2->boundingRect().height() + m_introLabel->boundingRect().height()) / 2);
		}
	}
}

void GameScene::start() {
	// If the introduction and new level labels were displayed then remove them
	if (items().contains(m_introLabel)) {
		removeItem(m_introLabel);
	}
	if (items().contains(m_introLabel2)) {
		removeItem(m_introLabel2);
	}
	if (items().contains(m_newLevelLabel)) {
		removeItem(m_newLevelLabel);
	}
}

void GameScene::setPaused(const bool p_pause, const bool p_fromUser) {
	// If the game has paused
	if (p_pause) {
		// If the pause is due to an action from the user
		if (p_fromUser) {
			// If the label was not displayed yet
			if (!items().contains(m_pauseLabel)) {
				// Display the pause label
				addItem(m_pauseLabel);
				m_pauseLabel->setPos((width() - m_pauseLabel->boundingRect().width()) / 2, (height() - m_pauseLabel->boundingRect().height()) / 2);
			}
		}
		// Stop kapman animation
		m_kapmanItem->pauseAnim();
	} else {	// If the game has resumed
		// If the pause was due to an action from the user
		if (p_fromUser) {
			// If the label was displayed
			if (items().contains(m_pauseLabel)) {
				removeItem(m_pauseLabel);
			}
		}
		// Resume kapman animation
		m_kapmanItem->resumeAnim();
	}
}

void GameScene::hideElement(const qreal p_x, const qreal p_y) {
	if (items().contains(m_elementItems[(int)((p_y - (Cell::SIZE * 0.5)) / Cell::SIZE)][(int)((p_x - (Cell::SIZE * 0.5)) / Cell::SIZE)])) {
		removeItem(m_elementItems[(int)((p_y - (Cell::SIZE * 0.5)) / Cell::SIZE)][(int)((p_x - (Cell::SIZE * 0.5)) / Cell::SIZE)]);
	}
}

void GameScene::displayBonus() {
	if (!items().contains(m_bonusItem)) {
		switch (m_game->getLevel()) {
			case 1:
				m_bonusItem->setElementId("chicken");
				break;
			case 2:
				m_bonusItem->setElementId("spider");
				break;
			case 3:
				m_bonusItem->setElementId("pizza");
				break;
			case 4:
				m_bonusItem->setElementId("donut");
				break;
			case 5:
				m_bonusItem->setElementId("tomato");
				break;
			case 6:
				m_bonusItem->setElementId("burger");
				break;
			default:
				m_bonusItem->setElementId("carrot");
				break;	
		}
		addItem(m_bonusItem);
	}
}

void GameScene::hideBonus() {
	if (items().contains(m_bonusItem)) {
		removeItem(m_bonusItem);
	}
}

void GameScene::updateInfo(const Game::InformationTypes p_info) {
	if (p_info & Game::LivesInfo) {
	    m_livesLabel->setPlainText(i18n("Lives : %1",m_game->getLives()));
	}
	if (p_info & Game::ScoreInfo) {
	    m_scoreLabel->setPlainText(i18n("Score : %1",m_game->getScore()));
	}
	if (p_info & Game::LevelInfo) {
	    QString level("Level : ");
	    level += QString::number((int)m_game->getLevel());
	    m_levelLabel->setPlainText(i18n("Level : %1",m_game->getLevel()));
	}
}

