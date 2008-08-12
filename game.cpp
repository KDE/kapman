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

Game::Game(KGameDifficulty::standardLevel p_difficulty) : m_isCheater(false), m_lives(3), m_points(0), m_level(1), m_nbEatenGhosts(0) {
	// Tells the KGameDifficulty singleton that the game is not running
	KGameDifficulty::setRunning(false);
	// Initialize the characters speed considering the difficulty level
	switch (p_difficulty) {
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
	// Create the Maze instance
	m_maze = new Maze();
	connect(m_maze, SIGNAL(allElementsEaten()), this, SLOT(nextLevel()));
	// Create the Kapman instance
	m_kapman = new Kapman(0.0, 0.0, m_maze);
	connect(m_kapman, SIGNAL(sWinPoints(Element*)), this, SLOT(winPoints(Element*)));
	// Create the Ghost instances
	m_ghosts.append(new Ghost(0.0, 0.0, "ghostred.svg", m_maze));
	m_ghosts.append(new Ghost(0.0, 0.0, "ghostgreen.svg", m_maze));
	m_ghosts.append(new Ghost(0.0, 0.0, "ghostblue.svg", m_maze));
	m_ghosts.append(new Ghost(0.0, 0.0, "ghostpink.svg", m_maze));
	for (int i = 0; i < m_ghosts.size(); i++) {
		connect(m_ghosts[i], SIGNAL(lifeLost()), this, SLOT(kapmanDeath()));
		connect(m_ghosts[i], SIGNAL(ghostEaten(Ghost*)), this, SLOT(ghostDeath(Ghost*)));
	}
	// Initialize the ghosts speed and the ghost speed increase considering the characters speed
	Ghost::initGhostsSpeed();
	// Create the Bonus instance
	m_bonus = new Bonus(qreal(Cell::SIZE * 14),qreal(Cell::SIZE * 18), m_maze, 100);
	m_bonusTimer = new QTimer(this);
	m_bonusTimer->setInterval(10000);
	m_bonusTimer->setSingleShot(true);
	connect(m_bonusTimer, SIGNAL(timeout()), this, SLOT(hideBonus()));
	// Start the Game timer
	m_timer = new QTimer(this);
	m_timer->setInterval(int(1000 / Game::FPS));
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
	m_state = RUNNING;
	// Init the characters coordinates on the Maze
	initCharactersPosition();
}

Game::~Game() {
	delete m_timer;
	delete m_bonusTimer;
	delete m_maze;
	delete m_kapman;
	for (int i = 0; i < m_ghosts.size(); i++) {
		delete m_ghosts[i];
	}
	delete m_bonus;
}

void Game::start() {
	// Restart the Game timer
	m_timer->start();
	m_state = RUNNING;
	emit(pauseChanged(false, false));
}

void Game::pause(bool p_locked) {
	// Stop the Game timer
	m_timer->stop();
	if (p_locked) {
		m_state = PAUSED_LOCKED;
	} else {
		m_state = PAUSED_UNLOCKED;
	}
	emit(pauseChanged(true, false));
}

void Game::switchPause(bool p_locked) {
	// If the Game is not already paused
	if (m_state == RUNNING) {
		// Pause the Game
		pause(p_locked);
		emit(pauseChanged(true, true));
	}
	// If the Game is already paused
	else {
		// Resume the Game
		start();
		emit(pauseChanged(false, true));
	}
}

Kapman* Game::getKapman() const {
	return m_kapman;
}
		
QList<Ghost*> Game::getGhosts () const {
	return m_ghosts;
}

QTimer* Game::getTimer() const {
	return m_timer;
}

Maze* Game::getMaze() const {
	return m_maze;
}

bool Game::isPaused() const {
	return (m_state != RUNNING);
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

void Game::initCharactersPosition() {
	// If the timer is stopped, it means that collisions are already being handled
	if (m_timer->isActive()) {	
		// At the beginning, the timer is stopped but the Game isn't paused (to allow keyPressedEvent detection)
		m_timer->stop();
		m_state = RUNNING;
		// Initialize Ghost coordinates and state
		m_ghosts[0]->setX(Cell::SIZE * 14);
		m_ghosts[0]->setY(Cell::SIZE * 11.5);
		m_ghosts[0]->setState(Ghost::HUNTER);
		m_ghosts[1]->setX(Cell::SIZE * 12);
		m_ghosts[1]->setY(Cell::SIZE * 14.5);
		m_ghosts[1]->setState(Ghost::HUNTER);
		m_ghosts[2]->setX(Cell::SIZE * 14);
		m_ghosts[2]->setY(Cell::SIZE * 14.5);
		m_ghosts[2]->setState(Ghost::HUNTER);
		m_ghosts[3]->setX(Cell::SIZE * 16);
		m_ghosts[3]->setY(Cell::SIZE * 14.5);
		m_ghosts[3]->setState(Ghost::HUNTER);
		// Initialize the Kapman coordinates
		m_kapman->setX(Cell::SIZE * 14);
		m_kapman->setY(Cell::SIZE * 23.5);
		m_kapman->init();
		// Initialize the Pills & Energizers coordinates
		for (int i = 0; i < m_maze->getNbRows(); i++) {
			for (int j = 0; j < m_maze->getNbColumns(); j++) {
				if (m_maze->getCell(i,j).getElement() != NULL){
					m_maze->getCell(i,j).getElement()->setX(Cell::SIZE * (j + 0.5));
					m_maze->getCell(i,j).getElement()->setY(Cell::SIZE * (i + 0.5));
				}
			}
		}
	}
}

void Game::keyPressEvent(QKeyEvent* p_event) {
	// At the beginning or when paused, we start the timer when an arrow key is pressed
	if ((p_event->key() == Qt::Key_Up || p_event->key() == Qt::Key_Down || p_event->key() ==  Qt::Key_Left || p_event->key() == Qt::Key_Right) && !m_timer->isActive()) {
		// If paused
		if (m_state == PAUSED_UNLOCKED) {
			switchPause();
		} else if (m_state == RUNNING) {	// At the game beginning
			// Start the game
			m_timer->start();
			emit(gameStarted());
		}
		// Tells the KGameDifficulty singleton that the game now runs
		KGameDifficulty::setRunning(true);
	}
	// Behaviour when the game has begun
	switch (p_event->key()) {
		case Qt::Key_Up:
			if (m_state == RUNNING) {
				m_kapman->goUp();
			}
			break;
		case Qt::Key_Down:
			if (m_state == RUNNING) {
				m_kapman->goDown();
			}
			break;
		case Qt::Key_Right:
			if (m_state == RUNNING) {
				m_kapman->goRight();
			}
			break;
		case Qt::Key_Left:
			if (m_state == RUNNING) {
				m_kapman->goLeft();
			}
			break;
		case Qt::Key_P:
			switchPause();
			break;
		case Qt::Key_K:
			// Cheat code to get one more life
			if (p_event->modifiers() == (Qt::AltModifier | Qt::ControlModifier | Qt::ShiftModifier)) {
				m_lives++;
				m_isCheater = true;
				emit(dataChanged(LivesInfo));
			}
		default:
			break;
	}
}

void Game::update() {
	int curKapmanRow, curKapmanCol;
	
	// Check if the kapman is in the line of sight of a ghost
	curKapmanRow = m_maze->getRowFromY(m_kapman->getY());
	curKapmanCol = m_maze->getColFromX(m_kapman->getX());
	
	for (int i = 0; i < m_ghosts.size(); i++) {
		if (m_ghosts[i]->getState() == Ghost::HUNTER && m_ghosts[i]->isInLineSight(m_kapman)) {
			m_ghosts[i]->updateMove(curKapmanRow, curKapmanCol);
		}
		else {
			m_ghosts[i]->updateMove();
		}
	}	
	m_kapman->updateMove();
	m_kapman->emitGameUpdated();
}

void Game::kapmanDeath() {
	m_lives--;
	m_kapman->die();
	emit(dataChanged(LivesInfo));
	// Make a 2 seconds pause while the kapman is blinking
	pause(true);
	QTimer::singleShot(2500, this, SLOT(resumeAfterKapmanDeath()));
}

void Game::resumeAfterKapmanDeath() {
	// Start the timer
	start();
	// Remove a possible bonus
	emit(bonusOff());
	// If their is no lives left, we start a new game
	if (m_lives <= 0) {
		emit(gameOver(true));
	} else {
		emit(levelStarted(false));
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
		// TODO 
	}
	else {
		m_points += p_element->getPoints();
	}	
	// For each 10000 points we get a life more
	if (m_points / 10000 > (m_points - p_element->getPoints()) / 10000) {
		m_lives++;
		emit(dataChanged(LivesInfo));
	}
	// If the eaten element is an energyzer we change the ghosts state
	if (p_element->getType() == Element::ENERGYZER) {
		for (int i = 0; i < m_ghosts.size(); i++) {
			if(m_ghosts[i]->getState() != Ghost::EATEN) {
				m_ghosts[i]->setState(Ghost::PREY);
			}
		}
		// Reset the number of eaten ghosts
		m_nbEatenGhosts = 0;
		emit(elementEaten(p_element->getX(), p_element->getY()));
	}
	else if (p_element->getType() == Element::PILL) {
		emit(elementEaten(p_element->getX(), p_element->getY()));
	}
	else if (p_element->getType() == Element::BONUS) {
		emit(bonusOff());
	}
	// If 1/3 or 2/3 of the pills are eaten
	if (m_maze->getNbElem() == m_maze->getTotalNbElem() / 3 || m_maze->getNbElem() == (m_maze->getTotalNbElem() * 2 / 3)) {
		// Display the Bonus
		emit(bonusOn());
		m_bonusTimer->start();
	}	
	emit(dataChanged(ScoreInfo));
}

void Game::nextLevel() {
	// Increment the level
	m_level++;
	// Initialize the maze items
	m_maze->resetNbElem();
	// Update Bonus
	m_bonus->setPoints(m_level * 100);
	// Increase the ghosts speed
	Ghost::increaseGhostsSpeed();
	// Move all characters to their initial positions
	initCharactersPosition();
	// Update the score, level and lives labels
	emit(dataChanged(AllInfo));
	// Update the view
	emit(levelStarted(true));
}

void Game::hideBonus() {
	emit(bonusOff());
}

