/*
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * Copyright 2007-2008 Pierre-Benoit Besse <besse@gmail.com>
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

const int Game::FPS = 40;

Game::Game(KGameDifficulty::standardLevel p_level) : m_isCheater(false), m_lives(3), m_points(0), m_level(1), m_nbEatenGhosts(0) {

	m_maze = new Maze();
	m_kapman = new Kapman(0.0, 0.0, m_maze);

	// Init the ghosts speed considering the difficulty level
	switch(p_level) {
		case KGameDifficulty::Easy:
			Character::setCharactersSpeed(Character::LOW_SPEED);
			break;
		case KGameDifficulty::Medium:
			Character::setCharactersSpeed(Character::MEDIUM_SPEED);
			break;
		case KGameDifficulty::Hard:
			Character::setCharactersSpeed(Character::HIGH_SPEED);
			break;
		default:
			break;
	}
	// Initialize the ghosts speed and speed increase considering the characters speed
	Ghost::initGhostsSpeed();
	// Tells to the KGameDifficulty singleton that the game is not running
	KGameDifficulty::setRunning(false);
	
	// Create the bonus
	m_bonus = new Bonus(qreal(Cell::SIZE *14),qreal(Cell::SIZE *18), m_maze, 100);
	
	m_ghostList.append(new Ghost(0.0, 0.0, "ghostred.svg", m_maze));
	m_ghostList.append(new Ghost(0.0, 0.0, "ghostgreen.svg", m_maze));
	m_ghostList.append(new Ghost(0.0, 0.0, "ghostblue.svg", m_maze));
	m_ghostList.append(new Ghost(0.0, 0.0, "ghostpink.svg", m_maze));

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
	m_timer->setInterval(int(1000 / Game::FPS));
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
	
	// Create the bonus timer
	m_bonusTimer = new QTimer(this);
	m_bonusTimer->setInterval(10000);
	m_bonusTimer->setSingleShot(true);
	connect(m_bonusTimer, SIGNAL(timeout()), this, SLOT(hideBonus()));

	// Init the characters
	initCharactersPosition();

//	m_media = Phonon::createPlayer(Phonon::GameCategory, KStandardDirs::locate("sound", "kapman/gamebegin.wav"));
//	m_media->play();
}

Game::~Game() {
	delete m_timer;
	delete m_bonusTimer;
	delete m_maze;
	delete m_kapman;
	for (int i = 0; i < m_ghostList.size(); i++) {
		delete m_ghostList[i];
	}
	delete m_bonus;
//	delete m_media;
}

void Game::start() {
	// Restart all active timers
	m_timer->start();
	
	// Tells the Game that it is no longer paused
	m_isPaused = false;
}

void Game::pause() {
	// Stop all timers
	m_timer->stop();
	// Tells the Game that it is paused
	m_isPaused = true;
}

void Game::doPause() {
	// If the game isn't paused yet, we stop all timers
	if(!m_isPaused) {
		pause();
		// Signal to the scene to add a 'PAUSE' label
		emit(managePause(true));
	}
	// If the game is already paused, we restart all timers
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

bool Game::isCheater() const {
	return m_isCheater;
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
		// Tells to the KGameDifficulty singleton that the game now runs
		KGameDifficulty::setRunning(true);
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
			if (p_event->modifiers() == (Qt::AltModifier | Qt::ControlModifier | Qt::ShiftModifier)) {
				m_lives++;
				m_isCheater = true;
				emit(updatingInfos(LivesInfo));
			}
		case Qt::Key_G:
			// Debug ghost pathfinding
			m_ghostList[0]->setState(Ghost::EATEN);
			break;
		default:
			break;
	}
}

/** SLOTS */
void Game::update() {
	int curKapmanRow, curKapmanCol;
	
	//check if the kapman is in the line of sight of a ghost
	curKapmanRow = m_maze->getRowFromY(m_kapman->getY());
	curKapmanCol = m_maze->getColFromX(m_kapman->getX());
	
	for(int i = 0; i < m_ghostList.size(); i++) {
		if(m_ghostList[i]->getState() == Ghost::HUNTER && m_ghostList[i]->isInLineSight(m_kapman)) {
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
	m_lives--;
	emit(updatingInfos(LivesInfo));
	m_kapman->die();
	// Make a 2 seconds pause while the kapman is blinking
	pause();
	QTimer::singleShot(2500, this, SLOT(resumeAfterKapmanDeath()));
}

void Game::resumeAfterKapmanDeath() {
	// Start the timer
	start();
	// Remove a possible bonus
	emit(sHideBonus());
	// If their is no lives left, we start a new game
	if (m_lives == 0) {
		emit(startnewgame(true));
	} else {
		emit(sDisplayLabel(false));
		// Move all characters to their initial positions
		initCharactersPosition();
	}
}

void Game::ghostDeath(Ghost* p_ghost) {
	m_nbEatenGhosts++;
	p_ghost->setState(Ghost::EATEN);
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
		emit(updatingInfos(LivesInfo));
	}
	// If the eaten element is an energyzer we change the ghosts state
	if(p_element->getType() == Element::ENERGYZER) {
		for (int i = 0; i < m_ghostList.size(); i++) {
			m_ghostList[i]->setState(Ghost::PREY);
		}
		// Reset the number of eaten ghosts
		m_nbEatenGhosts = 0;
		emit(sKillElement(p_element->getX(), p_element->getY()));
	}
	else if(p_element->getType() == Element::PILL) {
		emit(sKillElement(p_element->getX(), p_element->getY()));
	}
	else if(p_element->getType() == Element::BONUS) {
		emit(sHideBonus());
	}
	
	// If 1/3 or 2/3 of the pills are eaten, display a bonus
	if(m_maze->getNbElem() == m_maze->getTotalNbElem()/3 || m_maze->getNbElem() == (m_maze->getTotalNbElem()*2/3)) {
		emit(sDisplayBonus());
		m_bonusTimer->start();
	}	
	
	// Update view
	emit(updatingInfos(ScoreInfo));
}

void Game::nextLevel() {
	// Increment the level
	m_level++;
	// Increase the ghosts speed
	Ghost::increaseGhostsSpeed();
	// Move all characters to their initial positions
	initCharactersPosition();
	// To update the score, level and lives labels
	emit(updatingInfos(AllInfo));
	// To reinit the maze items
	emit(leveled());
	m_maze->resetNbElem();
	// Update Bonus
	m_bonus->setPoints(m_level * 100);
	emit(sDisplayLabel(true));
}

void Game::hideBonus() {
	emit(sHideBonus());
}
