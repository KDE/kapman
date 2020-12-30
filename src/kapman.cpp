/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kapman.h"

#include <KgDifficulty>

const qreal Kapman::MAX_SPEED_RATIO = 1.5;

Kapman::Kapman(qreal p_x, qreal p_y, Maze *p_maze) : Character(p_x, p_y, p_maze)
{
    m_type = Element::KAPMAN;
    m_maxSpeed = m_normalSpeed * MAX_SPEED_RATIO;
}

Kapman::~Kapman()
{

}

void Kapman::init()
{
    goRight();
    updateDirection();
    // Stop animation
    Q_EMIT stopped();
}

void Kapman::goUp()
{
    m_askedXSpeed = 0;
    m_askedYSpeed = -m_speed;
}

void Kapman::goDown()
{
    m_askedXSpeed = 0;
    m_askedYSpeed = m_speed;
}

void Kapman::goRight()
{
    m_askedXSpeed = m_speed;
    m_askedYSpeed = 0;
}

void Kapman::goLeft()
{
    m_askedXSpeed = -m_speed;
    m_askedYSpeed = 0;
}

void Kapman::updateDirection()
{
    setXSpeed(m_askedXSpeed);
    setYSpeed(m_askedYSpeed);
    m_askedXSpeed = 0;
    m_askedYSpeed = 0;
    // Signal to the kapman item that the direction changed
    Q_EMIT directionChanged();
}

void Kapman::updateMove()
{
    // If the kapman does not move
    if (m_xSpeed == 0 && m_ySpeed == 0) {
        // If the user asks for moving
        if (m_askedXSpeed != 0 || m_askedYSpeed != 0) {
            // Check the next cell with the asked direction
            if (getAskedNextCell().getType() == Cell::CORRIDOR) {
                // Update the direction
                updateDirection();
                // Move the kapman
                move();
            }
        }
    }
    // If the kapman is already moving
    else {
        // If the kapman wants to go back it does not wait to be on a center
        if ((m_xSpeed != 0 && m_askedXSpeed == -m_xSpeed) || (m_ySpeed != 0 && m_askedYSpeed == -m_ySpeed)) {
            // Go back
            updateDirection();
            // If the kapman just turned at a corner and instantly makes a half-turn, do not run into a wall
            if (isOnCenter() && getNextCell().getType() != Cell::CORRIDOR) {
                // Stop moving
                stopMoving();
            } else {
                // Move the kapman
                move();
            }
        } else {
            // If the kapman gets on a cell center
            if (onCenter()) {
                // If there is an asked direction (not a half-turn) and the corresponding next cell is accessible
                if ((m_askedXSpeed != 0 || m_askedYSpeed != 0)
                    && (m_askedXSpeed != m_xSpeed || m_askedYSpeed != m_ySpeed)
                    && (getAskedNextCell().getType() == Cell::CORRIDOR)) {
                    // Move the kapman on the cell center
                    moveOnCenter();
                    // Update the direction
                    updateDirection();
                } else {
                    // Check the next cell with the kapman current direction
                    if (getNextCell().getType() != Cell::CORRIDOR) {
                        // Move the kapman on the cell center
                        moveOnCenter();
                        // Stop moving
                        stopMoving();
                    } else {
                        // Move the kapman
                        move();
                    }
                }
            } else {
                // Move the kapman
                move();
            }
        }
    }
}

void Kapman::winPoints(Element *p_element)
{
    // Emits a signal to the game
    Q_EMIT sWinPoints(p_element);
}

void Kapman::die()
{
    Q_EMIT eaten();
}

void Kapman::emitGameUpdated()
{
    Q_EMIT gameUpdated();
}

qreal Kapman::getAskedXSpeed() const
{
    return m_askedXSpeed;
}

qreal Kapman::getAskedYSpeed() const
{
    return m_askedYSpeed;
}

Cell Kapman::getAskedNextCell()
{
    // Get the current cell coordinates from the character coordinates
    int curCellRow = m_maze->getRowFromY(m_y);
    int curCellCol = m_maze->getColFromX(m_x);
    Cell nextCell;

    // Get the next cell function of the character asked direction
    if (m_askedXSpeed > 0) {
        nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
    } else if (m_askedXSpeed < 0) {
        nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
    } else if (m_askedYSpeed > 0) {
        nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
    } else if (m_askedYSpeed < 0) {
        nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
    }

    return nextCell;
}

void Kapman::stopMoving()
{
    setXSpeed(0);
    setYSpeed(0);
    m_askedXSpeed = 0;
    m_askedYSpeed = 0;
    Q_EMIT stopped();
}

void Kapman::initSpeedInc()
{
    // Kapman speed increase when level up
    switch ((int) Kg::difficultyLevel()) {
    case KgDifficultyLevel::Easy:
        m_speedIncrease = Character::LOW_SPEED_INC / 2;
        break;
    case KgDifficultyLevel::Medium:
        m_speedIncrease = Character::MEDIUM_SPEED_INC / 2;
        break;
    case KgDifficultyLevel::Hard:
        m_speedIncrease = Character::HIGH_SPEED_INC / 2;
        break;
    }
}
