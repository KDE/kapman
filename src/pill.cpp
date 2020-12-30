/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
    SPDX-FileCopyrightText: 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pill.h"
#include "kapman.h"

const int Pill::POINTS = 10;

Pill::Pill(qreal p_x, qreal p_y, Maze *p_maze, const QString &p_imageId) : Element(p_x, p_y, p_maze)
{
    Element::setImageId(p_imageId);
    m_points = Pill::POINTS;
    m_type = Element::PILL;
}

Pill::~Pill()
{
}

void Pill::doActionOnCollision(Kapman *p_kapman)
{
    p_kapman->winPoints(this);
    // Tell to the maze that an element was eaten
    m_maze->decrementNbElem();
}

