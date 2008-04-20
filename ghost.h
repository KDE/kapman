/*
 * Copyright 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
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

#ifndef __GHOST_H
#define __GHOST_H

#include "character.h"
#include "kapman.h"

/**
 * This class represents the ghost
 */
class Ghost : public Character {

	Q_OBJECT
	
	public:
	
		/** The ghost possible state */
		enum GhostState {
			HUNTER = 0,
			PREY = 1,
			WHITE_PREY = 2
		};

	private:

		/** URL to the ghost's image */
		QString m_imageURL;
		
		/** The ghost actual state */
		GhostState m_state;
		
		/** The ghosts speed (different from Character::s_speed since it is increased on level up) */
		static qreal s_speed;

		/** The value the ghosts speed is incremented by when level up */
		static qreal s_speedIncrease;

		/** The possible speed increase (may change function of the difficulty level) */
		const static qreal LOW_SPEED_INC;
		const static qreal MEDIUM_SPEED_INC;
		const static qreal HIGH_SPEED_INC;

		/** The ghost speed (different from Ghost::s_speed since m_speed can change function of the ghost state) */
		qreal m_speed;

	public:

		/**
		 * Creates a new Ghost instance
		 * @param p_x the initial x-coordinate
		 * @param p_x the initial x-coordinate
		 * @param p_imageURL path to the image of the related item
		 * @param p_maze the maze the Ghost is on
		 */
		Ghost(qreal p_x, qreal p_y, const QString & p_imageURL, Maze* p_maze);

		/**
		 * Deletes the Ghost instance
		 */
		~Ghost();

		/**
		 * Updates the Ghost move
		 */
		void updateMove();

		/**
		 * Updates the Ghost with a direction to follow
		 * @param p_row x coordinate of the cell to reach
		 * @param p_col y coordinate of the cell to reach
		 */
		void updateMove(int p_row, int p_col);
		 
		/**
		 * @return the URL to the ghost's image
		 */
		QString getImageURL() const;
		
		/**
		 * @return the ghost state
		 */
		GhostState getState() const;
		
		/**
		 * Set the ghost state to the given value
		 * @param p_state the new state
		 */
		void setState(Ghost::GhostState p_state);
		
		 /**
		  * Manages the collison with the kapman
		  * @param p_kapman reference to the kapman model
		  */
		 void doActionOnCollision(Kapman* p_kapman);

		 /**
		  * Initializes the ghosts speed from the characters speed
		  */
		 static void initGhostsSpeed();

		 /**
		  * Increases the ghosts speed
		  */
		 static void increaseGhostsSpeed();

	private:

		/**
		 * Makes the Ghost go up
		 */
		void goUp();

		/**
		 * Makes the Ghost go down
		 */
		void goDown();

		/**
		 * Makes the Ghost go to the right
		 */
		void goRight();

		/**
		 * Makes the Ghost go to the left
		 */
		void goLeft();
		
	signals:
	
		/**
		 * Signals to the game that the kapman lost a life
		 */
		void lifeLost();
		
		/**
		 * Signals to the game that the ghost has been eaten
		 * @param p_ghost reference to the eaten ghost
		 */
		void ghostEaten(Ghost* p_ghost);
		
		/**
		 * Signals to its item that its state has changed
		 */
		void stateChanged();
};

#endif
