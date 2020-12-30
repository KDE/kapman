/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "character.h"

#include <KgDifficulty>

const qreal Character::LOW_SPEED = 3.75;
const qreal Character::MEDIUM_SPEED = 4.5;
const qreal Character::HIGH_SPEED = 5.25;
const qreal Character::LOW_SPEED_INC = 0.005;
const qreal Character::MEDIUM_SPEED_INC = 0.01;
const qreal Character::HIGH_SPEED_INC = 0.02;

Character::Character(qreal p_x, qreal p_y, Maze *p_maze) : Element(p_x, p_y, p_maze), m_xSpeed(0), m_ySpeed(0)
{
    initSpeed();
    m_maxSpeed = m_normalSpeed; // To avoid bugs, but will be overridden in the Ghost and Kapman constructors
}

Character::~Character()
{
}

void Character::move()
{
    // Take care of the Maze borders
    if (m_maze->getColFromX(m_x + m_xSpeed) == 0) {                                 // First column
        m_x = (m_maze->getNbColumns() - 1.5) * Cell::SIZE;
    } else if (m_maze->getColFromX(m_x + m_xSpeed) == m_maze->getNbColumns() - 1) { // Last column
        m_x = 1.5 * Cell::SIZE;
    } else if (m_maze->getRowFromY(m_y + m_ySpeed) == 0) {                          // First row
        m_y = (m_maze->getNbRows() - 1.5) * Cell::SIZE;
    } else if (m_maze->getRowFromY(m_y + m_ySpeed) == m_maze->getNbRows() - 1) {    // Last row
        m_y = 1.5 * Cell::SIZE;
    }
    // Move the Character
    m_x += m_xSpeed;
    m_y += m_ySpeed;
    Q_EMIT moved(m_x, m_y);
}

void Character::die()
{
    Q_EMIT eaten();
}

qreal Character::getXSpeed() const
{
    return m_xSpeed;
}

qreal Character::getYSpeed() const
{
    return m_ySpeed;
}

qreal Character::getSpeed() const
{
    return m_speed;
}

qreal Character::getNormalSpeed() const
{
    return m_normalSpeed;
}

void Character::setXSpeed(qreal p_xSpeed)
{
    m_xSpeed = p_xSpeed;
}

void Character::setYSpeed(qreal p_ySpeed)
{
    m_ySpeed = p_ySpeed;
}

void Character::initSpeed()
{
    // Kapman speed increase when level up
    switch ((int) Kg::difficultyLevel()) {
    case KgDifficultyLevel::Easy:
        m_normalSpeed = Character::LOW_SPEED;
        break;
    case KgDifficultyLevel::Medium:
        m_normalSpeed = Character::MEDIUM_SPEED;
        break;
    case KgDifficultyLevel::Hard:
        m_normalSpeed = Character::HIGH_SPEED;
        break;
    }
    m_speed = m_normalSpeed;
}

void Character::increaseCharactersSpeed()
{
    m_normalSpeed += m_normalSpeed * m_speedIncrease;
    // Do not have a speed over the max allowed speed
    if (m_normalSpeed > m_maxSpeed) {
        m_normalSpeed = m_maxSpeed;
    }
    m_speed = m_normalSpeed;
}

bool Character::isInLineSight(Character *p_character)
{
    int curCallerRow;       // The current row of the Character
    int curCallerCol;       // The current column of the Character
    int curCharacterRow;    // The current row of the other Character
    int curCharacterCol;    // The current column of the other Character

    curCallerRow = m_maze->getRowFromY(m_y);
    curCallerCol = m_maze->getColFromX(m_x);
    curCharacterRow = m_maze->getRowFromY(p_character->getY());
    curCharacterCol = m_maze->getColFromX(p_character->getX());

    // If the two Characters are on the same row
    if (curCallerRow == curCharacterRow) {
        // If The Character is on the right of the other one and goes to the left
        if (curCallerCol > curCharacterCol && m_xSpeed < 0) {
            // Check there is a wall between them
            for (int i = curCharacterCol; i < curCallerCol; ++i) {
                if (m_maze->getCell(curCallerRow, i).getType() != Cell::CORRIDOR) {
                    return false;
                }
            }
            // If not, the other Character is in the line sight
            return true;
            // If the Character is on the left of the other one and goes to the right
        } else if (curCallerCol < curCharacterCol && m_xSpeed > 0) {
            // Check there is a wall between them
            for (int i = curCallerCol; i < curCharacterCol; ++i) {
                if (m_maze->getCell(curCallerRow, i).getType() != Cell::CORRIDOR) {
                    return false;
                }
            }
            // If not, the other Character is in the line sight
            return true;
        }
        // If the two Characters are on the same column
    } else if (curCallerCol == curCharacterCol) {
        // If The Character is on the bottom of the other one and goes up
        if (curCallerRow > curCharacterRow && m_ySpeed < 0) {
            // Check there is a wall between them
            for (int i = curCharacterRow; i < curCallerRow; ++i) {
                if (m_maze->getCell(i, curCallerCol).getType() != Cell::CORRIDOR) {
                    return false;
                }
            }
            // If not, the other Character is in the line sight
            return true;
            // If the Character is on the top of the other one and goes down
        } else if (curCallerRow < curCharacterRow && m_ySpeed > 0) {
            // Check there is a wall between them
            for (int i = curCallerRow; i < curCharacterRow; ++i) {
                if (m_maze->getCell(i, curCallerCol).getType() != Cell::CORRIDOR) {
                    return false;
                }
            }
            // If not, the other Character is in the line sight
            return true;
        }
    }
    // If the two Characters are not on the same row or column, they are not in the line of sight
    return false;
}

Cell Character::getNextCell()
{
    Cell nextCell;
    // Get the current cell coordinates from the character coordinates
    int curCellRow = m_maze->getRowFromY(m_y);
    int curCellCol = m_maze->getColFromX(m_x);

    // Get the next cell function of the character direction
    if (m_xSpeed > 0) {
        nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
    } else if (m_xSpeed < 0) {
        nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
    } else if (m_ySpeed > 0) {
        nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
    } else if (m_ySpeed < 0) {
        nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
    }

    return nextCell;
}

bool Character::onCenter()
{
    // Get the current cell center coordinates
    qreal centerX = (m_maze->getColFromX(m_x) + 0.5) * Cell::SIZE;
    qreal centerY = (m_maze->getRowFromY(m_y) + 0.5) * Cell::SIZE;
    bool willGoPast = false;

    // Will the character go past the center of the cell it's on ?
    // If goes right
    if (m_xSpeed > 0) {
        willGoPast = (m_x <= centerX && m_x + m_xSpeed >= centerX);
    }
    // If goes left
    else if (m_xSpeed < 0) {
        willGoPast = (m_x >= centerX && m_x + m_xSpeed <= centerX);
    }
    // If goes down
    else if (m_ySpeed > 0) {
        willGoPast = (m_y <= centerY && m_y + m_ySpeed >= centerY);
    }
    // If goes up
    else if (m_ySpeed < 0) {
        willGoPast = (m_y >= centerY && m_y + m_ySpeed <= centerY);
    }
    // If does not moe
    else {
        willGoPast = (m_x == centerX && m_y == centerY);
    }

    return willGoPast;
}

bool Character::isOnCenter()
{
    // Get the current cell center coordinates
    qreal centerX = (m_maze->getColFromX(m_x) + 0.5) * Cell::SIZE;
    qreal centerY = (m_maze->getRowFromY(m_y) + 0.5) * Cell::SIZE;

    return m_x == centerX && m_y == centerY;
}


void Character::moveOnCenter()
{
    setX((m_maze->getColFromX(m_x) + 0.5) * Cell::SIZE);
    setY((m_maze->getRowFromY(m_y) + 0.5) * Cell::SIZE);
}
