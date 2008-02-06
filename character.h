/* This file is part of Kapman.
   Created by Pierre-Benoit Besse <besse.pb@gmail.com>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
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

		/** The Ghost moving speed */
 		static const qreal SPEED;

	protected:

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
		 * @param p_c 
		 * @return true if the caller is in the same line than the character
		 *	   without wall between them and if it doesn't have to make a 
		 *	   half turn
		 */
		bool isInLineSight(Character * p_c);

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
};

#endif