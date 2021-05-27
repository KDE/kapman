/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ghost.h"

#include <QPointF>
#include <KgDifficulty>
#include <QRandomGenerator>
#include <cstdlib>
#include <ctime>

const qreal Ghost::MAX_SPEED_RATIO = 2.0;
const int Ghost::POINTS = 200;

Ghost::Ghost(qreal p_x, qreal p_y, const QString &p_imageId, Maze *p_maze) : Character(p_x, p_y, p_maze)
  , m_preyStateAlmostOver(false)
{
    // Initialize the ghost attributes
    m_imageId = p_imageId;
    m_points = Ghost::POINTS;
    m_type = Element::GHOST;
    m_state = Ghost::HUNTER;
    m_maxSpeed = m_normalSpeed * MAX_SPEED_RATIO;
    // Makes the ghost move as soon as the game is created
    goLeft();
}

Ghost::~Ghost()
{

}

void Ghost::goUp()
{
    m_xSpeed = 0;
    m_ySpeed = -m_speed;
}

void Ghost::goDown()
{
    m_xSpeed = 0;
    m_ySpeed = m_speed;
}

void Ghost::goRight()
{
    m_xSpeed = m_speed;
    m_ySpeed = 0;
}

void Ghost::goLeft()
{
    m_xSpeed = -m_speed;
    m_ySpeed = 0;
}

void Ghost::updateMove()
{
    // Get the current cell coordinates from the character coordinates
    int curCellRow = m_maze->getRowFromY(m_y);
    int curCellCol = m_maze->getColFromX(m_x);
    // Contains the different directions a ghost can choose when on a cell center
    QList<QPointF> directionsList;
    int nb = 0;

    // If the ghost is not "eaten"
    if (m_state != Ghost::EATEN) {
        // If the ghost gets on a Cell center
        if (onCenter()) {
            // We retrieve all the directions the ghost can choose (save the turning back)
            if (m_maze->getCell(curCellRow, curCellCol + 1).getType() == Cell::CORRIDOR ||
                    (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
                     m_maze->getCell(curCellRow, curCellCol + 1).getType() == Cell::GHOSTCAMP)) {
                if (m_xSpeed >= 0) {
                    directionsList.append(QPointF(m_speed, 0.0));
                }
            }
            if (m_maze->getCell(curCellRow + 1, curCellCol).getType() == Cell::CORRIDOR ||
                    (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
                     m_maze->getCell(curCellRow + 1, curCellCol).getType() == Cell::GHOSTCAMP)) {
                if (m_ySpeed >= 0) {
                    directionsList.append(QPointF(0.0, m_speed));
                }
            }
            if (m_maze->getCell(curCellRow - 1, curCellCol).getType() == Cell::CORRIDOR ||
                    (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
                     m_maze->getCell(curCellRow - 1, curCellCol).getType() == Cell::GHOSTCAMP)) {
                if (m_ySpeed <= 0) {
                    directionsList.append(QPointF(0.0, -m_speed));
                }
            }
            if (m_maze->getCell(curCellRow, curCellCol - 1).getType() == Cell::CORRIDOR ||
                    (m_maze->getCell(curCellRow, curCellCol).getType() == Cell::GHOSTCAMP &&
                     m_maze->getCell(curCellRow, curCellCol - 1).getType() == Cell::GHOSTCAMP)) {
                if (m_xSpeed <= 0) {
                    directionsList.append(QPointF(-m_speed, 0.0));
                }
            }
            // Random number generation to choose one of the directions
            nb = int(double(QRandomGenerator::global()->bounded(RAND_MAX)) / (double(RAND_MAX) + 1) * directionsList.size());
            // If there is no directions in the list, the character goes backward
            if (directionsList.size() == 0) {
                m_xSpeed = -m_xSpeed;
                m_ySpeed = -m_ySpeed;
            } else if ((m_xSpeed != 0 && m_xSpeed != directionsList[nb].x()) ||
                       (m_ySpeed != 0 && m_ySpeed != directionsList[nb].y())) {     // If the chosen direction isn't forward
                // We move the ghost on the center of the cell and update the directions
                moveOnCenter();
                m_xSpeed = directionsList[nb].x();
                m_ySpeed = directionsList[nb].y();
            }
        }
        // We move the ghost
        move();
    } else {    // If the ghost has been eaten
        if (onCenter()) {
            // If the ghost has not reached the camp yet
            if (m_pathToCamp.size() != 0) {
                // Go to the next cell to the camp
                updateMove(m_pathToCamp.first().y(), m_pathToCamp.first().x());
                // Remove the cell the ghost has reached from the path
                m_pathToCamp.removeFirst();
            } else {
                // If the ghost is not at home (that means it has just been eaten)
                if (curCellRow != m_maze->getResurrectionCell().y() || curCellCol != m_maze->getResurrectionCell().x()) {
                    // Compute the path to go back to the camp
                    m_pathToCamp = m_maze->getPathToGhostCamp(curCellRow, curCellCol);
                    if (!m_pathToCamp.isEmpty()) {
                        updateMove(m_pathToCamp.first().y(), m_pathToCamp.first().x());
                    } else {
                        // Set the ghost at home
                        m_x = m_maze->getResurrectionCell().x() * Cell::SIZE + Cell::SIZE / 2;
                        m_y = m_maze->getResurrectionCell().y() * Cell::SIZE + Cell::SIZE / 2;
                        setState(Ghost::HUNTER);
                    }
                } else {    // The ghost has reached the ghost camp
                    setState(Ghost::HUNTER);
                }
            }
        }
        move();
    }
}

void Ghost::updateMove(int p_row, int p_col)
{
    // Get the current cell coordinates from the ghost coordinates
    int curGhostRow = m_maze->getRowFromY(m_y);
    int curGhostCol = m_maze->getColFromX(m_x);

    if (onCenter()) {
        if (curGhostRow == p_row) {
            if (p_col > curGhostCol) {
                m_xSpeed = m_speed;
                m_ySpeed = 0;
            } else {
                m_xSpeed = -m_speed;
                m_ySpeed = 0;
            }
        } else {
            if (p_row > curGhostRow) {
                m_xSpeed = 0;
                m_ySpeed = m_speed;
            } else {
                m_xSpeed = 0;
                m_ySpeed = -m_speed;
            }
        }
    }
    // We move the ghost
    move();
}

QString Ghost::getImageId() const
{
    return m_imageId;
}

Ghost::State Ghost::getState() const
{
    return m_state;
}

void Ghost::setState(Ghost::State p_state)
{
    // Change the state
    m_state = p_state;
    switch (m_state) {
    case Ghost::PREY:
        m_speed = m_normalSpeed / 2;
        break;
    case HUNTER:
    case EATEN:
        m_speed = m_normalSpeed;
        break;
    }
    Q_EMIT stateChanged();
}

void Ghost::doActionOnCollision(Kapman *)
{
    switch (m_state) {
    case Ghost::HUNTER:
        Q_EMIT lifeLost();
        break;
    case Ghost::PREY:
        Q_EMIT ghostEaten(this);
        break;
    case Ghost::EATEN:
        // Do nothing
        break;
    }
}

void Ghost::initSpeedInc()
{
    // Ghosts speed increase when level up
    switch ((int) Kg::difficultyLevel()) {
    case KgDifficultyLevel::Easy:
        m_speedIncrease = Character::LOW_SPEED_INC;
        break;
    case KgDifficultyLevel::Medium:
        m_speedIncrease = Character::MEDIUM_SPEED_INC;
        break;
    case KgDifficultyLevel::Hard:
        m_speedIncrease = Character::HIGH_SPEED_INC;
        break;
    }
}

void Ghost::setPreyStateAlmostOverEnabled(bool enable)
{
    m_preyStateAlmostOver = enable;
}

bool Ghost::preyStateAlmostOver() const
{
    return m_preyStateAlmostOver;
}
