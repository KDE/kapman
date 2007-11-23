#include <KActionCollection>
#include <KStandardGameAction>
#include <KMessageBox>
#include <KLocalizedString>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include "kapmanmainwindow.h"

KapmanMainWindow::KapmanMainWindow() {
	// Create the game
	m_game = new Game();
	// Create the view displaying the game scene
	QGraphicsView* view = new QGraphicsView(m_game->getScene());
	// Set a black background
	view->setBackgroundBrush(Qt::black);
	setCentralWidget(view);
	// Set the window menus
	KStandardGameAction::gameNew(this, SLOT(newGame()), actionCollection());
	KStandardGameAction::quit(this, SLOT(close()), actionCollection());
	setupGUI();
}

KapmanMainWindow::~KapmanMainWindow() {

}

void KapmanMainWindow::newGame() {
	if(KMessageBox::warningYesNo(this,
		ki18n("Are you sure you want to quit the current game ?").toString(),
		ki18n("New game").toString()) == KMessageBox::Yes) {
		delete m_game;
		m_game = new Game();
	}
}

void KapmanMainWindow::close() {
	if(KMessageBox::warningYesNo(this,
		ki18n("Are you sure you want to quit Kapman ?").toString(),
		ki18n("Quit").toString()) == KMessageBox::Yes) {
		KXmlGuiWindow::close();
	}
}
