/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "cell.h"
#include "element.h"

const qreal Cell::SIZE = 20.0;

Cell::Cell() : m_type(Cell::WALL), m_element(nullptr), m_cost(0), m_parent(nullptr)
{
}

Cell::~Cell()
{
    m_element = nullptr;
    delete m_element;
}

Cell::Type Cell::getType() const
{
    return m_type;
}

void Cell::setType(Cell::Type p_type)
{
    m_type = p_type;
}

Element *Cell::getElement() const
{
    return m_element;
}

void Cell::setElement(Element *p_element)
{
    m_element = p_element;
}

int Cell::getCost() const
{
    return m_cost;
}

void Cell::setCost(const int p_cost)
{
    m_cost = p_cost;
}

Cell *Cell::getParent() const
{
    return m_parent;
}

void Cell::setParent(Cell *p_parent)
{
    m_parent = p_parent;
}

