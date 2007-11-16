#include <KActionCollection>
#include <KStandardGameAction>
#include <KDialog>
#include <KLocalizedString>
#include <QLabel>
#include "kapmanmainwindow.h"

KapmanMainWindow::KapmanMainWindow() {
	KStandardGameAction::gameNew(this, SLOT(askNewGame()), actionCollection());
	KStandardGameAction::quit(this, SLOT(askClose()), actionCollection());
	setupGUI();
}

KapmanMainWindow::~KapmanMainWindow() {

}

void KapmanMainWindow::askNewGame() {
	KDialog* dialog = new KDialog(this);
   	dialog->setCaption(ki18n("New game").toString());
   	dialog->setButtons(KDialog::Yes | KDialog::No);
	dialog->setMainWidget(new QLabel(
		ki18n("Are you sure you want to quit the current game ?").toString()));
	connect(dialog, SIGNAL(yesClicked()), this, SLOT(newGame()));
	dialog->show();
}

void KapmanMainWindow::askClose() {
	KDialog* dialog = new KDialog(this);
   	dialog->setCaption(ki18n("Quit").toString());
   	dialog->setButtons(KDialog::Yes | KDialog::No);
	dialog->setMainWidget(new QLabel(
		ki18n("Are you sure you want to quit Kapman ?").toString()));
	connect(dialog, SIGNAL(yesClicked()), this, SLOT(close()));
	dialog->show();
}

void KapmanMainWindow::newGame() {
	// new game
}
