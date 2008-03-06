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

#include "game.h"
#include <KStandardDirs>


Game::Game() : m_lives(3), m_points(0), m_level(1), m_nbEatenGhosts(0) {
	m_maze = new Maze();
	m_kapman = new Kapman(0.0, 0.0, m_maze);
	
	// Create the bonus
	QString bonusImage = QString("poulet_test.svg");
	int points = 100;
	m_bonus = new Bonus(qreal(Cell::SIZE *14),qreal(Cell::SIZE *18),m_maze,bonusImage,points);
	
	QString ghostImage = QString("redGhost_test.svg");
	m_ghostList.append(new Ghost(0.0, 0.0, ghostImage, m_maze));
	ghostImage = QString("greenGhost_test.svg");
	m_ghostList.append(new Ghost(0.0, 0.0, ghostImage, m_maze));
	ghostImage = QString("blueGhost_test.svg");
	m_ghostList.append(new Ghost(0.0, 0.0, ghostImage, m_maze));
	ghostImage = QString("pinkGhost_test.svg");
	m_ghostList.append(new Ghost(0.0, 0.0, ghostImage, m_maze));

	// Connects all ghosts to the "kapmanDeath" slot
	for (int i = 0; i < m_ghostList.size(); i++) {
		connect(m_ghostList[i], SIGNAL(lifeLost()), this, SLOT(kapmanDeath()));
		connect(m_ghostList[i], SIGNAL(ghostEaten(Ghost*)), this, SLOT(ghostDeath(Ghost*)));
	}
	// Connects the kapman to the "winPoints" slot
	connect(m_kapman, SIGNAL(sWinPoints(Element*)), this, SLOT(winPoints(Element*)));
	// Manage the end of levels
	connect(m_maze, SIGNAL(allElementsEaten()), this, SLOT(nextLevel()));

	// Start the timer to move the characters regulary
	m_timer = new QTimer(this);
	m_timer->setInterval(15); // 60 FPS
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
	
	// Create the energyzers timer
	m_energyzerTimer = new QTimer(this);
	m_energyzerTimer->setInterval(10000);
	m_energyzerTimer->setSingleShot(true);
	connect(m_energyzerTimer, SIGNAL(timeout()), this, SLOT(changeGhostsToHunter()));
	
	// Create the bonus timer
	m_bonusTimer = new QTimer(this);
	m_bonusTimer->setInterval(10000);
	m_bonusTimer->setSingleShot(true);
	connect(m_bonusTimer, SIGNAL(timeout()), this, SLOT(disableDisplayBonus()));
	
	initCharactersPosition();
}

Game::~Game() {
	delete m_timer;
	delete m_energyzerTimer;
	delete m_maze;
	delete m_kapman;
	for (int i = 0; i < m_ghostList.size(); i++) {
		delete m_ghostList[i];
	}
}

void Game::start() {
	m_timer->start();
	// TODO Start the timer but not from beginning !!!
	m_energyzerTimer->start();
	m_isPaused = false;
}

void Game::pause() {
	m_timer->stop();
	m_energyzerTimer->stop();
	m_isPaused = true;
}

void Game::doPause() {
	// If the game isn't paused yet, we stop the timer
	if(!m_isPaused) {
		pause();

		// Signal to the scene to add a 'PAUSE' label
		emit(managePause(true));
	}
	// If the game is already paused, we restart the timer
	else {
		start();
		
		// Signal to the scene to remove the 'PAUSE' label
		emit(managePause(false));
	}
}

Kapman * Game::getKapman() const {
	return m_kapman;
}
		
QList<Ghost*> Game::getGhostList () const {
	return m_ghostList;
}

QTimer * Game::getTimer() const {
	return m_timer;
}

Maze * Game::getMaze() const {
	return m_maze;
}

bool Game::isPaused() const {
	return m_isPaused;
}

int Game::getScore() const {
	return m_points;
}
int Game::getLives() const {
	return m_lives;
}

int Game::getLevel() const {
	return m_level;
}

Bonus* Game::getBonus() {
	return m_bonus;
}

/** Private */
void Game::initCharactersPosition() {
	// If the timer is stopped, it means that collisions are already being handled
	if(m_timer->isActive()) {
		
		// At the beginning, the timer is stopped but the game isn't paused (to allow keyPressedEvent detection)
		m_timer->stop();
		m_isPaused = false;	
		
		// Initialize ghosts position and state
		// TODO Mettre un attribut "initialPosition" dans chaque character, initialisé à partir du XML
		m_ghostList[0]->setX(Cell::SIZE * 14);
		m_ghostList[0]->setY(Cell::SIZE * 11.5);
		m_ghostList[0]->setState(Ghost::HUNTER);
		m_ghostList[1]->setX(Cell::SIZE * 12);
		m_ghostList[1]->setY(Cell::SIZE * 14.5);
		m_ghostList[1]->setState(Ghost::HUNTER);
		m_ghostList[2]->setX(Cell::SIZE * 14);
		m_ghostList[2]->setY(Cell::SIZE * 14.5);
		m_ghostList[2]->setState(Ghost::HUNTER);
		m_ghostList[3]->setX(Cell::SIZE * 16);
		m_ghostList[3]->setY(Cell::SIZE * 14.5);
		m_ghostList[3]->setState(Ghost::HUNTER);
		
		// Initialize the kapman position
		m_kapman->setX(Cell::SIZE * 14);
		m_kapman->setY(Cell::SIZE * 23.5);
		m_kapman->init();

		// Initialize the Pills & Energizers positions
		for(int i=0; i<m_maze->getNbRows(); i++) {
			for(int j=0; j<m_maze->getNbColumns(); j++) {
				if(m_maze->getCell(i,j).getElement() != NULL){
					m_maze->getCell(i,j).getElement()->setX(Cell::SIZE * (j + 0.5));
					m_maze->getCell(i,j).getElement()->setY(Cell::SIZE * (i + 0.5));
				}
			}
		}
	}
}

void Game::keyPressEvent(QKeyEvent* p_event) {
	// At the beginning, we start the timer when a key is pressed
	if(!m_isPaused && !m_timer->isActive()) {
		m_timer->start();
		emit(removeIntro());
	}
	// Behaviour when the game has begun
	switch (p_event->key()) {
		case Qt::Key_Up:
			if(!m_isPaused) {
				m_kapman->goUp();
			}
			break;
		case Qt::Key_Down:
			if(!m_isPaused) {
				m_kapman->goDown();
			}
			break;
		case Qt::Key_Right:
			if(!m_isPaused) {
				m_kapman->goRight();
			}
			break;
		case Qt::Key_Left:
			if(!m_isPaused) {
				m_kapman->goLeft();
			}
			break;
		case Qt::Key_P:
			doPause();
			break;
		case Qt::Key_K:
			// Cheat code to get one more life
			if (p_event->modifiers() == Qt::AltModifier | Qt::ControlModifier | Qt::ShiftModifier) {
				m_lives++;
				emit(updatingInfos());
			}
		default:
			break;
	}
}

void Game::updateBonus() {
	// change bonus's image and points
	QString bonusImage;
	int points;
	switch(m_level) {
		case 1:
			bonusImage = QString("poulet_test.svg");
			break;
		case 2:
			bonusImage = QString("araignee_test.svg");
			break;
		case 3:
			bonusImage = QString("pizza_test.svg");
			break;
		case 4:
			bonusImage = QString("donut_test.svg");
			break;
		case 5:
			bonusImage = QString("tomate_test.svg");
			break;
		case 6:
			bonusImage = QString("burger_test.svg");
			break;
		default:
			bonusImage = QString("carrot_test.svg");
			break;	
	}
	points = m_level * 100;

	m_bonus->update(bonusImage,points);
}

/** SLOTS */
void Game::update() {
	int curKapmanRow, curKapmanCol;
	
	//check if the kapman is in the line of sight of a ghost
	curKapmanRow = m_maze->getRowFromY(m_kapman->getY());
	curKapmanCol = m_maze->getColFromX(m_kapman->getX());
	
	for(int i=0; i<m_ghostList.size(); i++) {
		if(m_ghostList[i]->isInLineSight(m_kapman)) {
			m_ghostList[i]->updateMove(curKapmanRow, curKapmanCol);
		}
		else {
			m_ghostList[i]->updateMove();
		}
	}	
	m_kapman->updateMove();
	
	// tells to kapman to call the function that will emit a signal to Kapmanitem (in order to manage collisions)
	m_kapman->emitGameUpdated();
}

void Game::kapmanDeath() {
	m_lives --;
	emit(updatingInfos());
	if(m_lives == 0) {
		emit(startnewgame(true));
	}
	else{
		// Move all characters to their initial positions
		initCharactersPosition();
	}
}

void Game::ghostDeath(Ghost* p_ghost) {
	m_nbEatenGhosts++;
	p_ghost->setState(Ghost::HUNTER);
	p_ghost->setX(Cell::SIZE * 14);
	p_ghost->setY(Cell::SIZE * 14.5);
	winPoints(p_ghost);
}

void Game::winPoints(Element* p_element) {
	// If the eaten element is a ghost, win 200 * number of eaten ghosts since the energizer was eaten
	if (p_element->getType() == Element::GHOST) {
		m_points += p_element->getPoints() * m_nbEatenGhosts;
	}
	else {
		m_points += p_element->getPoints();
	}	
	// For each 10000 points we get a life more
	if (m_points / 10000 > (m_points - p_element->getPoints()) / 10000) {
		m_lives++;
	}
	// If the eaten element is an energyzer we change the ghosts state
	if(p_element->getType() == Element::ENERGYZER) {
		changeGhostsToPrey();
		// Reset the number of eaten ghosts
		m_nbEatenGhosts = 0;
		emit(sKillElement(p_element->getX(), p_element->getY()));
	}
	else if(p_element->getType() == Element::PILL) {
		emit(sKillElement(p_element->getX(), p_element->getY()));
	}
	else if(p_element->getType() == Element::BONUS) {
		emit(sKillBonus());
	}
	
	if(m_maze->getNbElem() == m_maze->getTotalNbElem()/3 || m_maze->getNbElem() == (m_maze->getTotalNbElem()*2/3)) {
		emit(sDisplayBonus());
		m_bonusTimer->start();
	}	
	
	// Update view
	emit(updatingInfos());
}

void Game::nextLevel() {
	// Increment the level
	m_level++;
	// Move all characters to their initial positions
	initCharactersPosition();
	// Increase the ghosts speed
	Ghost::increaseGhostsSpeed(0.05);
	// To update the score, level and lives labels
	emit(updatingInfos());
	// To reinit the maze items
	emit(leveled());
	m_maze->resetNbElem();
	// Update Bonus
	updateBonus();
}

void Game::changeGhostsToPrey() {
	m_energyzerTimer->start();
	for (int i=0; i<m_ghostList.size(); i++) {
		m_ghostList[i]->setState(Ghost::PREY);
	}
}

void Game::changeGhostsToHunter() {
	for (int i=0; i<m_ghostList.size(); i++) {
		m_ghostList[i]->setState(Ghost::HUNTER);
	}
}

void Game::disableDisplayBonus() {
	emit(sDisableDisplayBonus());
}


