/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
    SPDX-FileCopyrightText: 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Johann Hingue <yoan1703@hotmail.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bonus.h"
#include "kapman.h"

Bonus::Bonus(qreal p_x, qreal p_y, Maze *p_maze, int p_points) : Element(p_x, p_y, p_maze)
{
    m_points = p_points;
    m_type = Element::BONUS;
}

Bonus::~Bonus()
{

}

void Bonus::doActionOnCollision(Kapman *p_kapman)
{
    p_kapman->winPoints(this);
}

void Bonus::setPoints(const int p_points)
{
    m_points = p_points;
}

