/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <KAboutData>
#include <KCrash>

#include "kapman_version.h"
#include "kapmanmainwindow.h"

#include <KDBusService>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    KLocalizedString::setApplicationDomain(QByteArrayLiteral("kapman"));

    // About Kapman
    KAboutData about(QStringLiteral("kapman"),
                     i18n("Kapman"),
                     QStringLiteral(KAPMAN_VERSION_STRING),
                     i18n("Kapman: Go through the levels escaping ghosts!"),
                     KAboutLicense::GPL,
                     i18n("Copyright (c) 2007-2008 The KapTeam"),
                     QString(),
                     QStringLiteral("https://apps.kde.org/kapman"));
    // Alphabetical order of Developers of Kapman
    about.addAuthor(i18n("Alexandre Galinier"), i18n("Developer"), QStringLiteral("alex.galinier@gmail.com"));
    about.addAuthor(i18n("Nathalie Liesse"), i18n("Developer"), QStringLiteral("nathalie.liesse@gmail.com"));
    about.addAuthor(i18n("Ömer Fadıl USTA"), i18n("Developer"), QStringLiteral("omerusta@gmail.com"));
    about.addAuthor(i18n("Pierre-Benoit Besse"), i18n("Developer"), QStringLiteral("besse.pb@gmail.com"));
    about.addAuthor(i18n("Romain Castan"), i18n("Developer"), QStringLiteral("romaincastan@gmail.com"));
    about.addAuthor(i18n("Thomas Gallinari"), i18n("Developer"), QStringLiteral("tg8187@yahoo.fr"));
    about.addCredit(i18n("Roney Gomes"), i18n("Port to KgSound framework"), QStringLiteral("roney477@gmail.com"));

    KAboutData::setApplicationData(about);
    // Set the application icon
    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kapman")));

    KCrash::initialize();

    // Command line arguments
    QCommandLineParser parser;
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);

    KDBusService service;

    // Create the main window
    auto window = new KapmanMainWindow();
    // Show the main window
    window->show();
    // Execute the application
    return app.exec();
}
