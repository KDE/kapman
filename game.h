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

#ifndef __GAME_H
#define __GAME_H

#include "maze.h"
#include "kapman.h"
#include "ghost.h"
#include "bonus.h"

#include <QTimer>
#include <QKeyEvent>
//#include <Phonon/MediaObject>
#include <KGameDifficulty>

/**
 * This class represents the game manager
 */
class Game : public QObject {

	Q_OBJECT

	private :

		/** Game timer */
		QTimer* m_timer;
		
		/** This timer only starts the m_switchTimer (when ghosts vulnerable time is nearly over) */
		QTimer* m_startSwitchingTimer;
		
		/** This timer makes all ghosts switch display */
		QTimer* m_switchTimer;
		
		/** Counts every switching of the ghosts (to stop after the fourth) */
		int m_switchTimerCount;
		
		/** Bonus Timer */
		QTimer* m_bonusTimer;
		
		/** Game Maze */
		Maze* m_maze;

		/** Main character */
		Kapman* m_kapman;
		
		/** Ghosts */
		QList<Ghost*> m_ghostList;

		/** pause flag */
		bool m_isPaused;
		
		/** indicates if the players cheated during the game */
		bool m_isCheater;

		/** Player's lives */
		int m_lives;
		
		/** Player's points */
		long m_points;

		/** Current level */
		int m_level;

		/** Number of eaten ghosts after eating an energizer */
		int m_nbEatenGhosts;
		
		/** Bonus */
		Bonus *m_bonus;
		
		/** The media to play sounds */
//		Phonon::MediaObject* m_media;

	public:

		enum Information { NoInfo = 0,
				   ScoreInfo = 1,
				   LivesInfo = 2,
				   LevelInfo = 4,
				   AllInfo = ScoreInfo | LivesInfo | LevelInfo };
		Q_DECLARE_FLAGS(InformationTypes, Information);

		/**
		 * Creates a new Game instance
		 * @param p_level the game level
		 */
		Game(KGameDifficulty::standardLevel p_level = KGameDifficulty::Medium);

		/**
		 * Deletes the Game instance
		 */
		~Game();

		/**
		 * Starts the game
		 */
		void start();

		/**
		 * Pauses the game
		 */
		void pause();

		/**
		 * Manage the game pause when 'P' key is pressed
		 */
		void doPause();

		/**
		 * @return the kapman model
		 */
		Kapman* getKapman() const;
		
		/**
		 * @return the list of ghosts models
		 */
		QList<Ghost*> getGhostList () const;
		
		/**
		 * @return the timer
		 */
		QTimer * getTimer() const;
		 
		 /**
		  * @return the maze
		  */
		 Maze * getMaze() const;
		 
		/**
		 * @return m_isPaused attribute
		 */
		bool isPaused() const;
		
		/**
		 * @return m_isCheater attribute
		 */
		bool isCheater() const;

		/**
		 * @return the score
		 */
		int getScore () const;

		/**
		 * @return the lifes
		 */
		int getLives() const;

		/**
		 * @return the current level
		 */
		int getLevel() const;
		
		/**
		 * @return the bonus
		 */
		Bonus* getBonus(); 

	private:
	
		/**
		 * Initialize the characters position when the game begin or when the kapman lose a life
		 */
		void initCharactersPosition();
		
		/**
		 * Change all ghost's state to 'prey'
		 */
		void changeGhostsToPrey();
		
		/**
		 * Makes all ghosts go back to 'hunter' state
		 */
		void changeGhostsToHunter();
		
		/**
		 * Update bonus
		 */
		void updateBonus();

	public slots:

		/**
		 * Called on key press event
		 * @param p_event the key press event
		 */
		void keyPressEvent(QKeyEvent* p_event);

		/**
		 * Called on each timer signal to update the game data
		 */
		void update();
		
		/**
		 * Manages the loss of a life
		 */
		void kapmanDeath();
		
		/**
		 * Manages the death of a ghost
		 */
		void ghostDeath(Ghost* p_ghost);

		/**
		 * Manages the points won
		 * @param p_elements reference to the eaten element
		 */
		void winPoints(Element* p_element);

		/**
		 * Start the next level
		 */
		void nextLevel();
		
		/**
		 * Start the switching of ghosts (when their vulnerable time is nearly over)
		 */
		void startGhostsSwitching();
		
		/**
		 * Switch the ghosts state
		 */
		void switchGhosts();
		
		/**
		 * Disable the display of the bonus
		 */
		void disableDisplayBonus();
		
	signals:
	
		/**
		 * Signals to the scene to display/remove the 'PAUSE' label
		 * @param p_pauseGame indicates if the game is to be paused or not
		 */
		void managePause(bool p_pauseGame);
		
		/**
		 * Signals to the scene to remove the 'INTRO' label
		 */
		void removeIntro();
		
		/**
		 * Signals to the scene to remove a Pill or Energizer
		 * @param p_x x coordinate of the element
		 * @param p_y y coordinate of the element
		 */
		void sKillElement(qreal p_x, qreal p_y);
		
		/**
		 * Signals to the scene to display a Bonus
		 */
		void sDisplayBonus();
		
		/**
		 * Signals to the scene to display the Label associated to a life losted or a new level!
		 */
		void sDisplayLabel(bool newlevel);

		/**
		 * Signals to the scene to remove a Bonus
		 */
		void sKillBonus();
		
		/**
		 * Signals to the scene to disable a Bonus
		 */
		void sDisableDisplayBonus();
		
		/**
		 * Signals to the scene to update the score and lives' labels
		 */
		void updatingInfos(Game::InformationTypes types);

		/**
		 * Signal to the kapmanmainwindow to start a newgame when there isn't more lives or when a level is finished
		 * @param p_gameFinished true if a level was finished, false if a Game Over was reached
		 */
		void startnewgame(bool p_gameFinished);

		/**
		 * Emitted when the level has been finished
		 */
		void leveled();
};

#endif
