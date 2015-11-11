/*
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

#include <QApplication>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <kdelibs4configmigrator.h>
#include <KDBusService>
#include "kapmanmainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Kdelibs4ConfigMigrator migrate(QStringLiteral("kapman"));
    migrate.setConfigFiles(QStringList() << QStringLiteral("kapmanrc"));
    migrate.setUiFiles(QStringList() << QStringLiteral("kapmanui.rc"));
    migrate.migrate();
    KLocalizedString::setApplicationDomain("kapman");
    // About Kapman
    KAboutData about(QStringLiteral("kapman"), i18n("Kapman"), QLatin1String("1.1.0"),
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
    parser.addVersionOption();
    parser.addHelpOption();
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);
    KDBusService service;
    // Set the application incon
    app.setWindowIcon(QIcon::fromTheme(QStringLiteral("kapman")));
    // Create the main window
    KapmanMainWindow *window = new KapmanMainWindow();
    // Show the main window
    window->show();
    // Execute the application
    return app.exec();
}

