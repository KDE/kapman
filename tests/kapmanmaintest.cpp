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
#include <QTest>

#include "kapmantest.h"
#include "ghosttest.h"
#include "charactertest.h"
#include "gametest.h"

int main() {

	KapmanTest kapObj;
	QTest::qExec(&kapObj);

	GhostTest ghoObj;
	QTest::qExec(&ghoObj);
	
	CharacterTest chaObj;
	QTest::qExec(&chaObj);
	
	GameTest gamObj;
	QTest::qExec(&gamObj);

	return 0;
}
