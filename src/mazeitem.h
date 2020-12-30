/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Pierre-Benoît Besse <besse.pb@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAZEITEM_H
#define MAZEITEM_H

#include <QGraphicsSvgItem>

/**
 * @brief This class is the graphical view of the Maze.
 */
class MazeItem : public QGraphicsSvgItem
{

    Q_OBJECT

public:

    /**
     * Creates a new MazeItem instance.
     */
    MazeItem();

    /**
     * Deletes the MazeItem instance.
     */
    ~MazeItem() override;
};

#endif

