/*
 * Copyright 2007-2008 Nathalie Liesse <nathalie.liesse@gmail.com>
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

#include "kapmanparser.h"
#include "element.h"
#include "pill.h"
#include "energizer.h"

KapmanParser::KapmanParser(Game *p_game)
{
    m_game = p_game;
    m_counterRows = 0;
}

KapmanParser::~KapmanParser()
{

}

bool KapmanParser::characters(const QString &ch)
{
    m_buffer = ch;
    return true;
}

bool KapmanParser::startElement(const QString &, const QString &, const QString &p_qName, const QXmlAttributes &p_atts)
{
    qreal x_position = 0.0;
    qreal y_position = 0.0;

    if (p_qName == QLatin1String("Maze")) {
        int nbRows = 0;
        int nbColumns = 0;
        // Initialize the number of rows and columns
        for (int i = 0; i < p_atts.count(); ++i) {
            if (p_atts.qName(i) == QLatin1String("rowCount")) {
                nbRows = p_atts.value(i).toInt();
            }
            if (p_atts.qName(i) == QLatin1String("colCount")) {
                nbColumns = p_atts.value(i).toInt();
            }
        }
        // Create the Maze matrix
        m_game->getMaze()->init(nbRows, nbColumns);
    } else if (p_qName == QLatin1String("Bonus")) {
        // Initialize the number of rows and columns
        for (int i = 0; i < p_atts.count(); ++i) {
            if (p_atts.qName(i) == QLatin1String("rowIndex")) {
                y_position = p_atts.value(i).toInt();
            }
            if (p_atts.qName(i) == QLatin1String("colIndex")) {
                x_position = p_atts.value(i).toInt();
            }
            if (p_atts.qName(i) == QLatin1String("x-align")) {
                if (p_atts.value(i) == QLatin1String("center")) {
                    x_position += 0.5;
                }
            }
            if (p_atts.qName(i) == QLatin1String("y-align")) {
                if (p_atts.value(i) == QLatin1String("center")) {
                    y_position += 0.5;
                }
            }
        }
        m_game->createBonus(QPointF(x_position, y_position));
    } else if (p_qName == QLatin1String("Kapman")) {
        // Initialize the number of rows and columns
        for (int i = 0; i < p_atts.count(); ++i) {
            if (p_atts.qName(i) == QLatin1String("rowIndex")) {
                y_position = p_atts.value(i).toInt();
            }
            if (p_atts.qName(i) == QLatin1String("colIndex")) {
                x_position = p_atts.value(i).toInt();
            }
            if (p_atts.qName(i) == QLatin1String("x-align")) {
                if (p_atts.value(i) == QLatin1String("center")) {
                    x_position += 0.5;
                }
            }
            if (p_atts.qName(i) == QLatin1String("y-align")) {
                if (p_atts.value(i) == QLatin1String("center")) {
                    y_position += 0.5;
                }
            }
        }
        m_game->createKapman(QPointF(x_position, y_position));
    } else if (p_qName == QLatin1String("Ghost")) {
        QString imageId;
        // Initialize the number of rows and columns
        for (int i = 0; i < p_atts.count(); ++i) {
            if (p_atts.qName(i) == QLatin1String("rowIndex")) {
                y_position = p_atts.value(i).toInt();
            }
            if (p_atts.qName(i) == QLatin1String("colIndex")) {
                x_position = p_atts.value(i).toInt();
            }
            if (p_atts.qName(i) == QLatin1String("x-align")) {
                if (p_atts.value(i) == QLatin1String("center")) {
                    x_position += 0.5;
                }
            }
            if (p_atts.qName(i) == QLatin1String("y-align")) {
                if (p_atts.value(i) == QLatin1String("center")) {
                    y_position += 0.5;
                }
            }
            if (p_atts.qName(i) == QLatin1String("imageId")) {
                imageId = p_atts.value(i);
            }
        }
        m_game->createGhost(QPointF(x_position, y_position), imageId);
    }

    return true;
}

bool KapmanParser::endElement(const QString &, const QString &, const QString &p_qName)
{
    if (p_qName == QLatin1String("Row")) {
        for (int i = 0; i < m_buffer.length(); ++i) {
            switch (m_buffer.at(i).toLatin1()) {
            case '|':
            case '=': m_game->getMaze()->setCellType(m_counterRows, i, Cell::WALL);
                break;
            case ' ': m_game->getMaze()->setCellType(m_counterRows, i, Cell::CORRIDOR);
                break;
            case '.': m_game->getMaze()->setCellType(m_counterRows, i, Cell::CORRIDOR);
                m_game->getMaze()->setCellElement(m_counterRows, i,
                                                  new Pill(m_counterRows, i, m_game->getMaze(), QLatin1String("pill")));
                break;
            case 'o': m_game->getMaze()->setCellType(m_counterRows, i, Cell::CORRIDOR);
                m_game->getMaze()->setCellElement(m_counterRows, i,
                                                  new Energizer(m_counterRows, i, m_game->getMaze(), QLatin1String("energizer")));
                break;
            case 'x': m_game->getMaze()->setCellType(m_counterRows, i, Cell::GHOSTCAMP);
                break;
            case 'X': m_game->getMaze()->setCellType(m_counterRows, i, Cell::GHOSTCAMP);
                m_game->getMaze()->setResurrectionCell(QPoint(m_counterRows, i));
                break;
            }
        }
        ++m_counterRows;
    }
    return true;
}

