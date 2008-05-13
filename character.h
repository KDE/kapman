/*
 * Copyright 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>
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

#ifndef __CHARACTER_H
#define __CHARACTER_H

#include "element.h"

/**
 * This class describes the main characteristics of the Kapman and the ghosts
 */
class Character : public Element {

	Q_OBJECT

	public:

		/** The characters possible speed */
		static const qreal LOW_SPEED;
		static const qreal MEDIUM_SPEED;
		static const qreal HIGH_SPEED;

	protected:

		/** The characters speed */
 		static qreal s_speed;

		/** Character speed */
		qreal m_xSpeed, m_ySpeed;

	public:

		/**
		 * Creates a new Character instance
		 * @param p_x the initial x coordinate
		 * @param p_y the initial y coordinate
		 * @param p_maze the maze the character is on
		 */
		Character(qreal p_x, qreal p_y, Maze* p_maze);

		/**
		 * Deletes the Character instance
		 */
		~Character();

		/**
		 * Makes the Character go up
		 */
		virtual void goUp() = 0;

		/**
		 * Makes the Character go down
		 */
		virtual void goDown() = 0;

		/**
		 * Makes the Character go to the right
		 */
		virtual void goRight() = 0;

		/**
		 * Makes the Character go to the left
		 */
		virtual void goLeft() = 0;

		/**
		 * Updates the character move
		 */
		virtual void updateMove() = 0;

		/**
		 * Moves the Character function of its coordinates and speed
		 * If the character reaches a border, it circles around the maze
		 * and continue its way from the other side
		 */
		void move();

		/**
		 * Manages the character death (essentially blinking)
		 */
		void die();

		/**
		 * @return the x speed value
		 */
		qreal getXSpeed() const;

		/**
		 * @return the y speed value
		 */
		qreal getYSpeed() const;
		
		/**
		 * Set the X speed attribute
		 * @param p_xSpeed the x speed attribute
		 */
		 void setXSpeed(qreal p_xSpeed);
		 
		 /**
		 * Set the Y speed attribute
		 * @param p_ySpeed the y speed attribute
		 */
		 void setYSpeed(qreal p_ySpeed);
		 
		 /**
		 * @param p_c the character to check
		 * @return true if the caller is in the same line than the character
		 *	   without wall between them and if it doesn't have to make a 
		 *	   half turn
		 */
		bool isInLineSight(Character * p_c);

		/**
		 * @return the characters speed
		 */
		static qreal getCharactersSpeed();

		/**
		 * Sets the characters speed
		 * @param p_speed the speed to set
		 */
		static void setCharactersSpeed(const qreal p_speed);

	protected:

		/**
		 * @return the next cell the character will move on with its current direction
		 */
		Cell getNextCell();

		/**
		 * If the character goes past the next center it mets during its next movement
		 * @return true if the character is on a center, false otherwise
		 */
		bool onCenter();

		/**
		 * Moves the character on its current cell center
		 */
		void moveOnCenter();

	signals:

		/**
		 * Emitted when the character is eaten
		 */
		void eaten();

};

#endif
