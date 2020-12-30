/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "game.h"
#include "elementitem.h"
#include "mazeitem.h"
#include "ghostitem.h"
#include "kapmanitem.h"

#include <QGraphicsScene>
#include <QList>
#include <QSvgRenderer>

#define USE_UNSTABLE_LIBKDEGAMESPRIVATE_API
#include <libkdegamesprivate/kgametheme.h>

/**
 * @brief This class contains all the Game elements to be drawn on the screen by the GameView instance.
 */
class GameScene : public QGraphicsScene
{

    Q_OBJECT

private:

    /** The Game instance */
    Game *m_game;

    /** The KapmanItem to be drawn */
    KapmanItem *m_kapmanItem;

    /** The MazeItem to be drawn */
    MazeItem *m_mazeItem;

    /** The GhostItem of each Ghost to be drawn */
    QList<GhostItem *> m_ghostItems;

    /** The ElementItem to be drawn (each Pill and Energizers) */
    ElementItem ** *m_elementItems;

    /** The Bonus ElementItem */
    ElementItem *m_bonusItem;

    /** A list with labels to display when a ghost or a bonus is eaten */
    QList<QGraphicsTextItem *> m_wonPointsLabels;

    /** The labels to be displayed during the game */
    QGraphicsTextItem *m_introLabel;
    QGraphicsTextItem *m_introLabel2;
    QGraphicsTextItem *m_newLevelLabel;
    QGraphicsTextItem *m_pauseLabel;

    /** The SVG renderer */
    QSvgRenderer *m_renderer;

    /** The Game theme */
    KGameTheme *m_theme;

public:

    /**
     * Creates a new GameScene instance.
     * @param p_game the Game instance whose elements must be contained in the GameScene in order to be drawn
     */
    explicit GameScene(Game *p_game);

    /**
     * Deletes the Game instance.
     */
    ~GameScene() override;

    /**
     * @return the Game instance
     */
    Game *getGame() const;

    /**
     * Loads the game theme.
     */
    void loadTheme();

private Q_SLOTS:

    /**
     * Updates the elements to be drawn on Game introduction.
     * @param p_newLevel true a new level has begun, false otherwise
     */
    void intro(const bool p_newLevel);

    /**
     * Updates the elements to be drawn when the Game starts.
     */
    void start();

    /**
     * Updates the elements to be drawn considering the Game state (paused or running).
     * @param p_pause if true the Game has been paused, if false the Game has been resumed
     * @param p_fromUser if true the Game has been paused due to an action from the user
     */
    void setPaused(const bool p_pause, const bool p_fromUser);

    /**
     * Removes the Element at the given coordinates from the GameScene.
     * @param p_wonPoints value of the won Points, used when a ghost or a Bonus is eaten
     * @param p_x x-coordinate of the Element
     * @param p_y y-coordinate of the Element
     */
    void hideElement(const qreal p_x, const qreal p_y);

    /**
     * Displays the Bonus.
     */
    void displayBonus();

    /**
     * Remove the Bonus from the GameScene.
     */
    void hideBonus();

    /**
     * Display won Points on the scene when a Bonus or a Ghosts is eaten
     * @param p_wonPoints the value to display
     * @param p_xPos the position of the eaten element on X axis
     * @param p_yPos the position of the eaten element on Y axis
     */
    void displayPoints(long p_wonPoints, qreal p_xPos, qreal p_yPos);

    /**
     * Hide the first label in the list of won points labels
     */
    void hidePoints();

    /**
     * Update theme id elements.
     */
    void updateSvgIds();

    /**
     * Update theme properties.
     */
    void updateThemeProperties();
};

#endif

