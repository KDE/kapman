/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gameview.h"
#include "gamescene.h"

GameView::GameView(Game *p_game) : QGraphicsView(new GameScene(p_game))
{
    setFrameStyle(QFrame::NoFrame);
    setFocusPolicy(Qt::StrongFocus);
    // Forward the key press events to the Game instance
    connect(this, &GameView::keyPressed, p_game, &Game::keyPressEvent);
}

GameView::~GameView()
{

}

void GameView::resizeEvent(QResizeEvent *)
{
    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void GameView::focusOutEvent(QFocusEvent *)
{
    // Pause the game if it is not already paused
    if (((GameScene *)scene())->getGame()->getTimer()->isActive()) {
        ((GameScene *)scene())->getGame()->switchPause();
    }
}

void GameView::keyPressEvent(QKeyEvent *p_event)
{
    Q_EMIT keyPressed(p_event);
}

