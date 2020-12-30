/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>
    SPDX-FileCopyrightText: 2007-2008 Alexandre Galinier <alex.galinier@hotmail.com>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gamescene.h"
#include "cell.h"
#include "bonus.h"
#include "settings.h"

#include <KLocalizedString>

GameScene::GameScene(Game *p_game) : m_game(p_game), m_kapmanItem(nullptr), m_mazeItem(nullptr)
{
    connect(p_game, &Game::levelStarted, this, &GameScene::intro);
    connect(p_game, &Game::gameStarted, this, &GameScene::start);
    connect(p_game, &Game::pauseChanged, this, &GameScene::setPaused);
    connect(p_game, &Game::elementEaten, this, &GameScene::hideElement);
    connect(p_game, &Game::bonusOn, this, &GameScene::displayBonus);
    connect(p_game, &Game::bonusOff, this, &GameScene::hideBonus);

    // Connection between Game and GameScene for the display of won points when a bonus or a ghost is eaten
    connect(p_game, &Game::pointsToDisplay, this, &GameScene::displayPoints);

    // Create the theme instance
    m_theme = new KGameTheme();

    // Load the SVG file
    m_renderer = new QSvgRenderer();
    loadTheme();

    // Create the MazeItem
    m_mazeItem = new MazeItem();
    // Give the maze the shared renderer to avoid loading the whole SVG file again
    m_mazeItem->setSharedRenderer(m_renderer);
    // Set the element Id to the right value
    m_mazeItem->setElementId(QStringLiteral("maze"));
    m_mazeItem->setZValue(-2);

    // Create the KapmanItem
    m_kapmanItem = new KapmanItem(p_game->getKapman());
    m_kapmanItem->setSharedRenderer(m_renderer);
    m_kapmanItem->setElementId(QStringLiteral("kapman_0"));
    // Corrects the position of the KapmanItem
    m_kapmanItem->update(p_game->getKapman()->getX(), p_game->getKapman()->getY());
    m_kapmanItem->setZValue(2);
    // Stops the Kapman animation
    m_kapmanItem->stopAnim();

    // Create the GhostItems
    for (int i = 0; i < p_game->getGhosts().size(); ++i) {
        GhostItem *ghost = new GhostItem(p_game->getGhosts()[i]);
        ghost->setSharedRenderer(m_renderer);
        ghost->setElementId(p_game->getGhosts()[i]->getImageId());
        ghost->update(p_game->getGhosts()[i]->getX(), p_game->getGhosts()[i]->getY());
        // At the beginning, the ghosts are above the kapman because they eat him
        ghost->setZValue(3);
        m_ghostItems.append(ghost);
    }
    // Create the Pill and Energizer items
    m_elementItems = new ElementItem **[m_game->getMaze()->getNbRows()];
    for (int i = 0; i < m_game->getMaze()->getNbRows(); ++i) {
        m_elementItems[i] = new ElementItem*[m_game->getMaze()->getNbColumns()];
        for (int j = 0; j < m_game->getMaze()->getNbColumns(); ++j) {
            if (m_game->getMaze()->getCell(i, j).getElement() != nullptr) {
                // Create the element and set the image
                ElementItem *element = new ElementItem(m_game->getMaze()->getCell(i, j).getElement());
                element->setSharedRenderer(m_renderer);
                element->setElementId(m_game->getMaze()->getCell(i, j).getElement()->getImageId());
                element->update(m_game->getMaze()->getCell(i, j).getElement()->getX(), m_game->getMaze()->getCell(i, j).getElement()->getY());
                m_elementItems[i][j] = element;
            } else {
                m_elementItems[i][j] = nullptr;
            }
        }
    }
    // Create the Bonus item
    m_bonusItem = new ElementItem(m_game->getBonus());
    m_bonusItem->setSharedRenderer(m_renderer);
    m_bonusItem->setElementId(QStringLiteral("bonus1"));

    // All elements are created, update theme properties
    updateSvgIds();
    updateThemeProperties();

    // Create the introduction labels
    m_introLabel = new QGraphicsTextItem(i18n("GET READY!!!"));
    m_introLabel->setFont(QFont(QStringLiteral("Helvetica"), 25, QFont::Bold, false));
    m_introLabel->setDefaultTextColor(QColor(QLatin1String("#FFFF00")));
    m_introLabel->setZValue(4);
    m_introLabel2 = new QGraphicsTextItem(i18n("Press any arrow key to start"));
    m_introLabel2->setFont(QFont(QStringLiteral("Helvetica"), 15, QFont::Bold, false));
    m_introLabel2->setDefaultTextColor(QColor(QLatin1String("#FFFF00")));
    m_introLabel2->setZValue(4);
    // Create the new level label
    m_newLevelLabel = new QGraphicsTextItem();
    m_newLevelLabel->setFont(QFont(QStringLiteral("Helvetica"), 35, QFont::Bold, false));
    m_newLevelLabel->setDefaultTextColor(QColor(QLatin1String("#FFFF00")));
    m_newLevelLabel->setZValue(4);
    // Create the pause label
    m_pauseLabel = new QGraphicsTextItem(i18n("PAUSED"));
    m_pauseLabel->setFont(QFont(QStringLiteral("Helvetica"), 35, QFont::Bold, false));
    m_pauseLabel->setDefaultTextColor(QColor(QLatin1String("#FFFF00")));
    m_pauseLabel->setZValue(4);

    // Display the MazeItem
    addItem(m_mazeItem);
    // Display the KapmanItem
    addItem(m_kapmanItem);
    // Display each GhostItem
    for (int i = 0; i < m_ghostItems.size(); ++i) {
        addItem(m_ghostItems[i]);
    }
    // Display each Pill and Energizer item and introduction labels
    intro(true);
}

GameScene::~GameScene()
{
    delete m_mazeItem;
    delete m_kapmanItem;
    for (int i = 0; i < m_ghostItems.size(); ++i) {
        delete m_ghostItems[i];
    }
    for (int i = 0; i < m_game->getMaze()->getNbRows(); ++i) {
        for (int j = 0; j < m_game->getMaze()->getNbColumns(); ++j) {
            if (m_elementItems[i][j] != nullptr) {
                delete m_elementItems[i][j];
            }
        }
        delete[] m_elementItems[i];
    }
    delete[] m_elementItems;
    delete m_bonusItem;
    delete m_introLabel;
    delete m_introLabel2;
    delete m_newLevelLabel;
    delete m_pauseLabel;
    delete m_renderer;
    delete m_theme;
}

Game *GameScene::getGame() const
{
    return m_game;
}

void GameScene::loadTheme()
{
    if (!m_theme->load(Settings::self()->theme())) {
        return;
    }
    if (!m_renderer->load(m_theme->graphics())) {
        return;
    }

    //Update elementIDs, theme properties
    updateSvgIds();
    updateThemeProperties();

    update(0, 0, width(), height());

    // Update the theme config: if the default theme is selected, no theme entry is written -> the theme selector does not select the theme
    Settings::self()->config()->group("General").writeEntry("Theme", Settings::self()->theme());
}

void GameScene::updateSvgIds()
{
    //Needed so new boundingRects() are read for all SVG elements after a theme change
    // Sanity check, see if game elements already exist
    if (!m_kapmanItem) {
        return;
    }

    // Set the element Id to the right value
    m_mazeItem->setElementId(QStringLiteral("maze"));

    // Create the KapmanItem
    m_kapmanItem->setElementId(QStringLiteral("kapman_0"));
    // Corrects the position of the KapmanItem
    m_kapmanItem->update(m_game->getKapman()->getX(), m_game->getKapman()->getY());

    for (int i = 0; i < m_ghostItems.size(); ++i) {
        GhostItem *ghost = m_ghostItems[i];
        ghost->setElementId(m_game->getGhosts()[i]->getImageId());
        ghost->update(m_game->getGhosts()[i]->getX(), m_game->getGhosts()[i]->getY());
    }
    for (int i = 0; i < m_game->getMaze()->getNbRows(); ++i) {
        for (int j = 0; j < m_game->getMaze()->getNbColumns(); ++j) {
            if (m_elementItems[i][j] != nullptr) {
                ElementItem *element = m_elementItems[i][j];
                element->setElementId(m_game->getMaze()->getCell(i, j).getElement()->getImageId());
                element->update(m_game->getMaze()->getCell(i, j).getElement()->getX(), m_game->getMaze()->getCell(i, j).getElement()->getY());
            }
        }
    }
}

void GameScene::updateThemeProperties()
{
    // Sanity check, see if game elements already exist
    if (!m_kapmanItem) {
        return;
    }

    // Set the Rotation flag for KapmanItem
    if (m_theme->themeProperty(QStringLiteral("RotateKapman")) == QLatin1String("0")) {
        m_kapmanItem->setRotationFlag(false);
    } else {
        m_kapmanItem->setRotationFlag(true);
    }
}

void GameScene::intro(const bool p_newLevel)
{
    // If a new level has begun
    if (p_newLevel) {
        // Set each Pill and Energizer item to its original coordinates
        for (int i = 0; i < m_game->getMaze()->getNbRows(); ++i) {
            for (int j = 0; j < m_game->getMaze()->getNbColumns(); ++j) {
                if (m_elementItems[i][j] != nullptr) {
                    if (!items().contains(m_elementItems[i][j])) {
                        addItem(m_elementItems[i][j]);
                    }
                }
            }
        }
        if (items().contains(m_introLabel)) {
            removeItem(m_introLabel);
        }
        // Display the new level label
        m_newLevelLabel->setPlainText(i18nc("The number of the game level", "Level %1", m_game->getLevel()));
        if (!items().contains(m_newLevelLabel)) {
            addItem(m_newLevelLabel);
            m_newLevelLabel->setPos((width() - m_newLevelLabel->boundingRect().width()) / 2, (height() - m_newLevelLabel->boundingRect().height()) / 2);
        }
        // Display the introduction label
        if (!items().contains(m_introLabel2)) {
            addItem(m_introLabel2);
            m_introLabel2->setPos((width() - m_introLabel2->boundingRect().width()) / 2,
                                  (height() - m_introLabel2->boundingRect().height() + m_newLevelLabel->boundingRect().height()) / 2);
        }
    } else {
        // Display the introduction labels
        if (!items().contains(m_introLabel)) {
            addItem(m_introLabel);
            m_introLabel->setPos((width() - m_introLabel->boundingRect().width()) / 2, (height() - m_introLabel->boundingRect().height()) / 2);
        }
        if (!items().contains(m_introLabel2)) {
            addItem(m_introLabel2);
            m_introLabel2->setPos((width() - m_introLabel2->boundingRect().width()) / 2,
                                  (height() - m_introLabel2->boundingRect().height() + m_introLabel->boundingRect().height()) / 2);
        }
    }
}

void GameScene::start()
{
    // If the introduction and new level labels were displayed then remove them
    if (items().contains(m_introLabel)) {
        removeItem(m_introLabel);
    }
    if (items().contains(m_introLabel2)) {
        removeItem(m_introLabel2);
    }
    if (items().contains(m_newLevelLabel)) {
        removeItem(m_newLevelLabel);
    }
}

void GameScene::setPaused(const bool p_pause, const bool p_fromUser)
{
    // If the game has paused
    if (p_pause) {
        // If the pause is due to an action from the user
        if (p_fromUser) {
            // If the label was not displayed yet
            if (!items().contains(m_pauseLabel)) {
                // FIXME: Hack to remove labels when pausing game while init labels are shown (icwiener)
                //        This should be done cleaner
                // FIXME #2: start() is a misleading method name ...
                start();
                // Display the pause label
                addItem(m_pauseLabel);
                m_pauseLabel->setPos((width() - m_pauseLabel->boundingRect().width()) / 2, (height() - m_pauseLabel->boundingRect().height()) / 2);
            }
        }
        // Stop kapman animation
        m_kapmanItem->pauseAnim();
    } else {    // If the game has resumed
        // If the pause was due to an action from the user
        if (p_fromUser) {
            // If the label was displayed
            if (items().contains(m_pauseLabel)) {
                removeItem(m_pauseLabel);
            }
        }
        // Resume kapman animation
        m_kapmanItem->resumeAnim();
    }
}

void GameScene::hideElement(const qreal p_x, const qreal p_y)
{
    if (items().contains(m_elementItems[(int)((p_y - (Cell::SIZE * 0.5)) / Cell::SIZE)][(int)((p_x - (Cell::SIZE * 0.5)) / Cell::SIZE)])) {
        removeItem(m_elementItems[(int)((p_y - (Cell::SIZE * 0.5)) / Cell::SIZE)][(int)((p_x - (Cell::SIZE * 0.5)) / Cell::SIZE)]);
    }
}

void GameScene::displayBonus()
{
    if (!items().contains(m_bonusItem)) {
        switch (m_game->getLevel()) {
        case 1:
            m_bonusItem->setElementId(QStringLiteral("bonus1"));
            break;
        case 2:
            m_bonusItem->setElementId(QStringLiteral("bonus2"));
            break;
        case 3:
            m_bonusItem->setElementId(QStringLiteral("bonus3"));
            break;
        case 4:
            m_bonusItem->setElementId(QStringLiteral("bonus4"));
            break;
        case 5:
            m_bonusItem->setElementId(QStringLiteral("bonus5"));
            break;
        case 6:
            m_bonusItem->setElementId(QStringLiteral("bonus6"));
            break;
        default:
            m_bonusItem->setElementId(QStringLiteral("bonus7"));
            break;
        }
        m_bonusItem->update(m_game->getBonus()->getX(), m_game->getBonus()->getY());
        addItem(m_bonusItem);
    }
}

void GameScene::hideBonus()
{
    if (items().contains(m_bonusItem)) {
        removeItem(m_bonusItem);
    }
}

void GameScene::displayPoints(long p_wonPoints, qreal p_xPos, qreal p_yPos)
{
    // Launch a singleShot timer
    QTimer::singleShot(1000, this, &GameScene::hidePoints);

    // Add a label in the list of won points Labels
    m_wonPointsLabels.prepend(new QGraphicsTextItem(QString::number(p_wonPoints)));
    addItem(m_wonPointsLabels.first());

    // Temporary reference to the first item in the list
    QGraphicsTextItem *tempRef = m_wonPointsLabels.first();

    // Positioning and customization of the point label
    tempRef->setDefaultTextColor(QColor(QLatin1String("#FFFF00")));
    tempRef->setFont(QFont(QStringLiteral("Helvetica"), 15, QFont::Normal, false));
    tempRef->setPos(p_xPos - (tempRef->boundingRect().width() / 2), p_yPos - (tempRef->boundingRect().height() / 2));
    tempRef->setZValue(-1);
}

void GameScene::hidePoints()
{
    // Remove the oldest item of the list from the scene
    removeItem(m_wonPointsLabels.last());
    // Remove the oldest item from the list
    delete m_wonPointsLabels.takeLast();
}
