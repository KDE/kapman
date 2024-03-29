/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Gaël Courcelle <gael.courcelle@gmail.com>
    SPDX-FileCopyrightText: 2007-2008 Alexia Allanic <alexia_allanic@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "energizer.h"
#include "kapman.h"

const int Energizer::POINTS = 50;

Energizer::Energizer(qreal p_x, qreal p_y, Maze *p_maze, const QString &p_imageId)
    : Element(p_x, p_y, p_maze)
{
    Element::setImageId(p_imageId);
    m_points = Energizer::POINTS;
    m_type = Element::ENERGYZER;
}

Energizer::~Energizer() = default;

void Energizer::doActionOnCollision(Kapman *p_kapman)
{
    p_kapman->winPoints(this);
    // Tell to the maze that an element was eaten
    m_maze->decrementNbElem();
}

#include "moc_energizer.cpp"
