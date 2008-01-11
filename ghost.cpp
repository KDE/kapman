/* This file is part of Kapman.
   Created by Alexandre GALINIER <alex.galinier@hotmail.com>

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

#include "ghost.h"
#include <cstdlib>
#include <QPointF>
#include "time.h"

Ghost::Ghost(qreal p_x, qreal p_y, QString p_imageURL, Maze* p_maze) : Character(p_x, p_y, p_maze) {
	m_imageURL = p_imageURL;

	// Put the red ghost on the center of its starting cell (FOR TESTS)
	moveOnCenter();

	// Initialize the random-number generator
	srand(time(NULL));

	// Makes the ghost move as soon as the game is created
	goLeft();
}

Ghost::~Ghost() {

}

void Ghost::goUp() {
	m_xSpeed = 0;
 	m_ySpeed = -SPEED;
}
 
void Ghost::goDown() {
	m_xSpeed = 0;
	m_ySpeed = SPEED;
}

void Ghost::goRight() {
	m_xSpeed = SPEED;
	m_ySpeed = 0;
}

void Ghost::goLeft() {
	m_xSpeed = -SPEED;
	m_ySpeed = 0;
}

void Ghost::updateMove() {
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(m_y);
	int curCellCol = m_maze->getColFromX(m_x);
	
	// Indicates if the character hasn't any choice of direction save backward
	bool halfTurnRequired = true;
	
	// This list is to contain the different directions a ghost can choose when on a cell center
	QList<QPointF*> directionsList;
	
	// If the ghost gets on a Cell center
	if( onCenter() ) {
	
		// We retrieve all the directions the ghost can choose (save the half turn)
		if(m_maze->getCell(curCellRow, curCellCol +1).getType() == Cell::CORRIDOR) {
			if(m_xSpeed >= 0) {
				directionsList.append(new QPointF(Ghost::SPEED, 0.0));
				halfTurnRequired = false;
			}
		}
		if(m_maze->getCell(curCellRow +1, curCellCol).getType() == Cell::CORRIDOR) {
			if(m_ySpeed >= 0) {
				directionsList.append(new QPointF(0.0, Ghost::SPEED));
				halfTurnRequired = false;
			}
		}
		if(m_maze->getCell(curCellRow -1, curCellCol).getType() == Cell::CORRIDOR) {
			if(m_ySpeed <= 0) {
				directionsList.append(new QPointF(0.0, -Ghost::SPEED));
				halfTurnRequired = false;
			}
		}
		
		if(m_maze->getCell(curCellRow, curCellCol -1).getType() == Cell::CORRIDOR) {
			if(m_xSpeed <= 0) {
				directionsList.append(new QPointF(-Ghost::SPEED, 0.0));
				halfTurnRequired = false;
			}
		}
		
		// Random number generation to choose one of the directions
		int nb = int( double(rand()) / (double(RAND_MAX) + 1) * directionsList.size() );
		
		// If there is no directions in the lists, the character goes backward
		if(directionsList.size() == 0) {
			m_xSpeed = -m_xSpeed;	
			m_ySpeed = -m_ySpeed;
		}
		// If the choosed direction isn't forward, we move the ghost on the center of the cell and update the directions
		else if( (m_xSpeed != 0 && m_xSpeed != directionsList[nb]->x()) 
				|| (m_ySpeed !=0 && m_ySpeed != directionsList[nb]->y())) {
			moveOnCenter();
			m_xSpeed = directionsList[nb]->x();
			m_ySpeed = directionsList[nb]->y();
		}	
	}
	
	// We move the ghost
	move();
}

QString Ghost::getImageURL() const  {
	return m_imageURL;
}
