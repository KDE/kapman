/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Nathalie Liesse <nathalie.liesse@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef KAPMANPARSER_H
#define KAPMANPARSER_H

#include "game.h"

#include <QXmlStreamAttributes>

/**
 * @brief This class handles XML reader events in order to initialize the Maze properties.
 */
class KapmanParser
{

private:

    /** The Game to initialize */
    Game *m_game;

    /** The parser's buffer */
    QString m_buffer;

    /** The rows counter */
    int m_counterRows;
public:

    /**
     * Creates a new GameParser.
     * @param p_game the Game to initialize
     */
    explicit KapmanParser(Game *p_game);

    /**
     * Deletes the GameParser instance.
     */
    ~KapmanParser();

    bool characters(const QStringRef &ch);

    bool startElement(const QStringRef &namespaceURI, const QStringRef &localName,
                      const QStringRef &qName, const QXmlStreamAttributes &atts);

    bool endElement(const QStringRef &namespaceURI,
                    const QStringRef &localName, const QStringRef &qName);

    bool parse(QIODevice *input);
};

#endif

