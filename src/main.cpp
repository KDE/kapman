/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <KAboutData>
#include <KCrash>

#include <QApplication>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <kdelibs4configmigrator.h>
#include <KDBusService>
#include "kapmanmainwindow.h"
#include "kapman_version.h"

int main(int argc, char **argv)
{
    // Fixes blurry icons with fractional scaling
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    Kdelibs4ConfigMigrator migrate(QStringLiteral("kapman"));
    migrate.setConfigFiles(QStringList() << QStringLiteral("kapmanrc"));
    migrate.setUiFiles(QStringList() << QStringLiteral("kapmanui.rc"));
    migrate.migrate();
    KLocalizedString::setApplicationDomain("kapman");
    // About Kapman
    KAboutData about(QStringLiteral("kapman"), i18n("Kapman"), QStringLiteral(KAPMAN_VERSION_STRING),
                     i18n("Kapman: Go through the levels escaping ghosts!"),
                     KAboutLicense::GPL, i18n("Copyright (c) 2007-2008 The KapTeam"));
    // Alphabetical order of Developers of Kapman
    about.addAuthor(i18n("Alexandre Galinier"), i18n("Developer"), QStringLiteral("alex.galinier@gmail.com"));
    about.addAuthor(i18n("Nathalie Liesse"), i18n("Developer"), QStringLiteral("nathalie.liesse@gmail.com"));
    about.addAuthor(i18n("Ömer Fadıl USTA"), i18n("Developer"), QStringLiteral("omerusta@gmail.com"));
    about.addAuthor(i18n("Pierre-Benoit Besse"), i18n("Developer"), QStringLiteral("besse.pb@gmail.com"));
    about.addAuthor(i18n("Romain Castan"), i18n("Developer"), QStringLiteral("romaincastan@gmail.com"));
    about.addAuthor(i18n("Thomas Gallinari"), i18n("Developer"), QStringLiteral("tg8187@yahoo.fr"));
    about.addCredit(i18n("Roney Gomes"), i18n("Port to KgSound framework"), QStringLiteral("roney477@gmail.com"));
    about.setHomepage(QStringLiteral("https://www.kde.org/applications/games/kapman/"));

    // Command line arguments
    QCommandLineParser parser;
    KAboutData::setApplicationData(about);
    KCrash::initialize();
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);
    KDBusService service;
    // Set the application icon
    app.setWindowIcon(QIcon::fromTheme(QStringLiteral("kapman")));
    // Create the main window
    KapmanMainWindow *window = new KapmanMainWindow();
    // Show the main window
    window->show();
    // Execute the application
    return app.exec();
}

