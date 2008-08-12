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

#ifndef __GAME_H
#define __GAME_H

#include "maze.h"
#include "kapman.h"
#include "ghost.h"
#include "bonus.h"

#include <QTimer>
#include <QKeyEvent>
#include <KGameDifficulty>

/**
 * @brief This class manages the game main loop : it regularly checks the key press events, computes the character moves and updates their coordinates.
 */
class Game : public QObject {

	Q_OBJECT

	private :

		/** Number of FPS */
		static const int FPS;

		/** The game different states : RUNNING, PAUSED_LOCKED, PAUSED_UNLOCKED */
		enum State {
			RUNNING,			// Game running
			PAUSED_LOCKED,		// Game paused and user is not allowed to unpause
			PAUSED_UNLOCKED		// Game paused and user is allowed to unpause
		};
		/** A flag for the State enum */
		Q_DECLARE_FLAGS(GameStates, State);

		/** The game state */
		State m_state;

		/** The Game main timer */
		QTimer* m_timer;
		
		/** The Bonus timer to make it disappear if it is not eaten after a given time */
		QTimer* m_bonusTimer;
		
		/** The Maze */
		Maze* m_maze;

		/** The main Character */
		Kapman* m_kapman;
		
		/** The Ghosts */
		QList<Ghost*> m_ghosts;
		
		/** The Bonus instance */
		Bonus *m_bonus;

		/** A flag to know if the player has cheated during the game */
		bool m_isCheater;

		/** The remaining number of lives */
		int m_lives;
		
		/** The won points */
		long m_points;

		/** The current game level */
		int m_level;

		/** The number of eaten ghosts since the beginning of the current level */
		int m_nbEatenGhosts;
		
	public:

		/** The different types of information about the game */
		enum Information { NoInfo = 0,
				   ScoreInfo = 1,	// Score
				   LivesInfo = 2,	// Number of remaining lives
				   LevelInfo = 4,	// Current level
				   AllInfo = ScoreInfo | LivesInfo | LevelInfo };
		/** A flag for the Information enum */
		Q_DECLARE_FLAGS(InformationTypes, Information);

		/**
		 * Creates a new Game instance.
		 * @param p_difficulty the KGameDifficulty level of the Game
		 */
		Game(KGameDifficulty::standardLevel p_difficulty = KGameDifficulty::Medium);

		/**
		 * Deletes the Game instance.
		 */
		~Game();

		/**
		 * Starts the Game.
		 */
		void start();

		/**
		 * Pauses the Game.
		 * @param p_locked if true the player will be unable to unset the pause.
		 */
		void pause(bool p_locked = false);

		/**
		 * Pauses / unpauses the game.
		 * @param p_locked if true the player will be unable to unset the pause.
		 */
		void switchPause(bool p_locked = false);

		/**
		 * @return the Maze instance
		 */
		Maze* getMaze() const;
		 
		/**
		 * @return the Kapman model
		 */
		Kapman* getKapman() const;
		
		/**
		 * @return the Ghost models
		 */
		QList<Ghost*> getGhosts () const;

		/**
		 * @return the Bonus instance
		 */
		Bonus* getBonus(); 
		
		/**
		 * @return the main timer
		 */
		QTimer* getTimer() const;
		 
		/**
		 * @return true if the Game is paused, false otherwise
		 */
		bool isPaused() const;
		
		/**
		 * @return true if the player has cheated during the game, false otherwise
		 */
		bool isCheater() const;

		/**
		 * @return the score
		 */
		int getScore () const;

		/**
		 * @return the number of remaining lives
		 */
		int getLives() const;

		/**
		 * @return the current level
		 */
		int getLevel() const;
		
	private:
	
		/**
		 * Initializes the character coordinates.
		 */
		void initCharactersPosition();

	public slots:

		/**
		 * Manages the key press events.
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent* p_event);
		
		/**
		 * Resumes the Game after the Kapman death.
		 */
		void resumeAfterKapmanDeath();
		
	private slots:

		/**
		 * Updates the Game data.
		 */
		void update();
		
		/**
		 * Manages the loss of a life.
		 */
		void kapmanDeath();

		/**
		 * Manages the death of a Ghost.
		 */
		void ghostDeath(Ghost* p_ghost);

		/**
		 * Increases the score considering the eaten Element.
		 * @param p_element the eaten Element
		 */
		void winPoints(Element* p_element);

		/**
		 * Starts the next level.
		 */
		void nextLevel();
		
		/**
		 * Hides the Bonus.
		 */
		void hideBonus();
		
	signals:
	
		/**
		 * Emitted when the Game is started.
		 */
		void gameStarted();
		
		/**
		 * Emitted when the Game is over.
		 * @param p_unused this parameter must always be true !
		 */
		void gameOver(const bool p_unused);

		/**
		 * Emitted when a level begins, if level up or if a life has been lost.
		 * @param p_newLevel true if a new level is beginning, false otherwise
		 */
		void levelStarted(const bool p_newLevel);
		
		/**
		 * Emitted when the pause state has changed.
		 * @param p_pause true if the Game is paused, false otherwise
		 * @param p_fromUser true if the Game has been paused due to an action the player has done, false otherwise
		 */
		void pauseChanged(const bool p_pause, const bool p_fromUser);
		
		/**
		 * Emitted when an Element has been eaten.
		 * @param p_x the Element x-coordinate
		 * @param p_y the Element y-coordinate
		 */
		void elementEaten(const qreal p_x, const qreal p_y);
		
		/**
		 * Emitted when the Bonus has to be displayed.
		 */
		void bonusOn();

		/**
		 * Emitted when the Bonus has to disappear.
		 */
		void bonusOff();
		
		/**
		 * Emitted when the Game data (score, level, lives) have changed.
		 * @param p_infoType the type of data that have changed
		 */
		void dataChanged(Game::InformationTypes p_infoType);
};

#endif

