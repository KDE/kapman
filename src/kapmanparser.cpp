/*
    SPDX-FileCopyrightText: 2007-2008 Nathalie Liesse <nathalie.liesse@gmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "kapmanparser.h"
#include "element.h"
#include "pill.h"
#include "energizer.h"
#include <QDebug>

KapmanParser::KapmanParser(Game *p_game)
{
    m_game = p_game;
    m_counterRows = 0;
}

KapmanParser::~KapmanParser()
{

}

bool KapmanParser::parse(QIODevice *input)
{
    QXmlStreamReader reader(input);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.hasError())
            return false;

        switch (reader.tokenType()) {
        case QXmlStreamReader::StartElement:
            if (!startElement(reader.namespaceUri(), reader.name(),
                              reader.qualifiedName(), reader.attributes())) {
                return false;
            }
            break;
        case QXmlStreamReader::EndElement:
            if (!endElement(reader.namespaceUri(), reader.name(),
                            reader.qualifiedName())) {
                return false;
            }
            break;
        case QXmlStreamReader::Characters:
            if (!reader.isWhitespace() && !reader.text().toString().trimmed().isEmpty()) {
                if (!characters(reader.text()))
                    return false;
            }
            break;
        default:
            break;
        }
    }

    if (!reader.isEndDocument())
        return false;

    return true;
}

bool KapmanParser::characters(const QStringRef &ch)
{
    m_buffer = ch.toString();
    return true;
}

bool KapmanParser::startElement(const QStringRef &namespaceURI, const QStringRef &localName, const QStringRef &qName, const QXmlStreamAttributes &atts)
{
    Q_UNUSED(namespaceURI)
    Q_UNUSED(localName)
    qreal x_position = 0.0;
    qreal y_position = 0.0;

    if (qName == QLatin1String("Maze")) {
        int nbRows = 0;
        int nbColumns = 0;
        // Initialize the number of rows and columns
        if (atts.hasAttribute(QLatin1String("rowCount"))) {
            nbRows = atts.value(QLatin1String("rowCount")).toInt();
        }
        if (atts.hasAttribute(QLatin1String("colCount"))) {
            nbColumns = atts.value(QLatin1String("colCount")).toInt();
        }
        // Create the Maze matrix
        m_game->getMaze()->init(nbRows, nbColumns);
    } else if (qName == QLatin1String("Bonus")) {
        // Initialize the number of rows and columns
        if (atts.hasAttribute(QLatin1String("rowIndex"))) {
            y_position = atts.value(QLatin1String("rowIndex")).toInt();
        }
        if (atts.hasAttribute(QLatin1String("colIndex"))) {
            x_position = atts.value(QLatin1String("colIndex")).toInt();
        }
        if (atts.hasAttribute(QLatin1String("x-align"))) {
            if (atts.value(QLatin1String("x-align")).toString() == QLatin1String("center")) {
                x_position += 0.5;
            }
        }
        if (atts.hasAttribute(QLatin1String("y-align"))) {
            if (atts.value(QLatin1String("y-align")).toString() == QLatin1String("center")) {
                y_position += 0.5;
            }
        }
        m_game->createBonus(QPointF(x_position, y_position));
    } else if (qName == QLatin1String("Kapman")) {
        if (atts.hasAttribute(QLatin1String("rowIndex"))) {
            y_position = atts.value(QLatin1String("rowIndex")).toInt();
        }
        if (atts.hasAttribute(QLatin1String("colIndex"))) {
            x_position = atts.value(QLatin1String("colIndex")).toInt();
        }
        if (atts.hasAttribute(QLatin1String("x-align"))) {
            if (atts.value(QLatin1String("x-align")).toString() == QLatin1String("center")) {
                x_position += 0.5;
            }
        }
        if (atts.hasAttribute(QLatin1String("y-align"))) {
            if (atts.value(QLatin1String("y-align")).toString() == QLatin1String("center")) {
                y_position += 0.5;
            }
        }

        m_game->createKapman(QPointF(x_position, y_position));
    } else if (qName == QLatin1String("Ghost")) {
        QString imageId;
        // Initialize the number of rows and columns
        if (atts.hasAttribute(QLatin1String("rowIndex"))) {
            y_position = atts.value(QLatin1String("rowIndex")).toInt();
        }
        if (atts.hasAttribute(QLatin1String("colIndex"))) {
            x_position = atts.value(QLatin1String("colIndex")).toInt();
        }
        if (atts.hasAttribute(QLatin1String("x-align"))) {
            if (atts.value(QLatin1String("x-align")).toString() == QLatin1String("center")) {
                x_position += 0.5;
            }
        }
        if (atts.hasAttribute(QLatin1String("y-align"))) {
            if (atts.value(QLatin1String("y-align")).toString() == QLatin1String("center")) {
                y_position += 0.5;
            }
        }
        if (atts.hasAttribute(QLatin1String("imageId"))) {
            imageId = atts.value(QLatin1String("imageId")).toString();
        }
        m_game->createGhost(QPointF(x_position, y_position), imageId);
    }

    return true;
}

bool KapmanParser::endElement(const QStringRef &namespaceURI, const QStringRef &localName, const QStringRef &qName)
{
    Q_UNUSED(namespaceURI)
    Q_UNUSED(localName)

    if (qName.toString() == QLatin1String("Row")) {
        for (int i = 0, total = m_buffer.length(); i < total; ++i) {
            switch (m_buffer.at(i).toLatin1()) {
            case '|':
            case '=':
                m_game->getMaze()->setCellType(m_counterRows, i, Cell::WALL);
                break;
            case ' ':
                m_game->getMaze()->setCellType(m_counterRows, i, Cell::CORRIDOR);
                break;
            case '.':
                m_game->getMaze()->setCellType(m_counterRows, i, Cell::CORRIDOR);
                m_game->getMaze()->setCellElement(m_counterRows, i,
                                                  new Pill(m_counterRows, i, m_game->getMaze(), QStringLiteral("pill")));
                break;
            case 'o':
                m_game->getMaze()->setCellType(m_counterRows, i, Cell::CORRIDOR);
                m_game->getMaze()->setCellElement(m_counterRows, i,
                                                  new Energizer(m_counterRows, i, m_game->getMaze(), QStringLiteral("energizer")));
                break;
            case 'x':
                m_game->getMaze()->setCellType(m_counterRows, i, Cell::GHOSTCAMP);
                break;
            case 'X':
                m_game->getMaze()->setCellType(m_counterRows, i, Cell::GHOSTCAMP);
                m_game->getMaze()->setResurrectionCell(QPoint(m_counterRows, i));
                break;
            }
        }
        ++m_counterRows;
    }
    return true;
}

