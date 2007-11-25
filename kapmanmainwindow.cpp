#include <KActionCollection>
#include <KStandardGameAction>
#include <KMessageBox>
#include <KLocalizedString>
#include "kapmanmainwindow.h"
#include "gameview.h"

KapmanMainWindow::KapmanMainWindow() {
	// Create the game
	m_game = new Game();
	// Create the view displaying the game scene
	m_view = new GameView(m_game->getScene());
	m_view->setBackgroundBrush(Qt::black);
	// Connect the key events to the game manager
	connect(m_view, SIGNAL(keyPressed(QKeyEvent*)),
		m_game, SLOT(keyPressEvent(QKeyEvent*)));
	setCentralWidget(m_view);
	// Set the window menus
	KStandardGameAction::gameNew(this, SLOT(newGame()), actionCollection());
	KStandardGameAction::quit(this, SLOT(close()), actionCollection());
	setupGUI();
}

KapmanMainWindow::~KapmanMainWindow() {
	delete m_game;
	delete m_view;
}

void KapmanMainWindow::newGame() {
	if(KMessageBox::warningYesNo(this,
		ki18n("Are you sure you want to quit the current game ?").toString(),
		ki18n("New game").toString()) == KMessageBox::Yes) {
		// Start a new game
		delete m_game;
		m_game = new Game();
		// Associate the view with the new game scene
		m_view->setScene(m_game->getScene());
	}
}

void KapmanMainWindow::close() {
	if(KMessageBox::warningYesNo(this,
		ki18n("Are you sure you want to quit Kapman ?").toString(),
		ki18n("Quit").toString()) == KMessageBox::Yes) {
		// Call the close() function of the parent class
		KXmlGuiWindow::close();
	}
}
