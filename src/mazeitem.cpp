/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mazeitem.h"

MazeItem::MazeItem() : QGraphicsSvgItem()
{
    // Configure the cache in order to increase the performance
    setCacheMode(DeviceCoordinateCache);
    setMaximumCacheSize(QSize(2000, 2000));
}

MazeItem::~MazeItem()
{

}

