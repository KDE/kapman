/* This file is part of Kapman.
   Created by Pierre-Benoit Besse <besse.pb@gmail.com>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
*/

#include "gametest.h"
#include "game.h"
#include "maze.h"
#include "cell.h"

void GameTest::testGame() {
	Game * game = new Game();
	
	// At the beggining the timer is stopped but the game isn't paused (to allow keyPress detection
	QCOMPARE(game->getTimer()->isActive(), FALSE);
	QCOMPARE(game->isPaused(), FALSE);
	QCOMPARE(game->getTimer()->interval(), 15);
}

QTEST_KDEMAIN_CORE(GameTest)
