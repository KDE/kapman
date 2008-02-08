/**
 * Copyright 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <KAboutData>
#include <KCmdLineArgs>
#include <KApplication>
#include "kapmanmainwindow.h"

int main(int argc, char** argv) {
	// About Kapman
	KAboutData about("kapman", 0, ki18n("Kapman"), "0.6.0",
		ki18n("Kapman : Go through the levels escaping ghosts"),
		KAboutData::License_GPL, ki18n("(c) 2007-2008 The KapTeam !"));
	// Command line arguments
	KCmdLineArgs::init(argc, argv, &about);
	// Create the application
	KApplication app;
	// Create the main window
	KapmanMainWindow* window = new KapmanMainWindow();
	// Show the main window
	window->show();
	// Execute the application
	return app.exec();
}
