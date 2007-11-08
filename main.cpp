#include <KAboutData>
#include <KCmdLineArgs>
#include <KApplication>
#include "kapmanmainwindow.h"

int main(int argc, char** argv) {
	// About Kapman
	KAboutData about("kapman", 0, ki18n("Kapman"), "0.0.1",
		ki18n("Kapman : Go through the levels escaping ghosts"),
		KAboutData::License_GPL,
		ki18n("(c) 2007-2008 The KapTeam !"));
	// Command line arguments
	KCmdLineArgs::init(argc, argv, &about);
	// Create the application
	KApplication app;
	// Create the main window
	KapmanMainWindow window;
	// Show the main window
	window.show();
	// Execute the application
	return app.exec();
}
