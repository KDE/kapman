#include <KActionCollection>
#include <KStandardGameAction>
#include "kapmanmainwindow.h"

KapmanMainWindow::KapmanMainWindow() {
	KStandardGameAction::gameNew(this, SLOT(newGame()), actionCollection());
	KStandardGameAction::quit(this, SLOT(close()), actionCollection());
	setupGUI();
}

KapmanMainWindow::~KapmanMainWindow() {

}

void KapmanMainWindow::newGame() {

}
