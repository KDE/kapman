/*
    SPDX-FileCopyrightText: 2007-2008 Thomas Gallinari <tg8187@yahoo.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ELEMENTITEM_H
#define ELEMENTITEM_H

#include <QGraphicsSvgItem>

#include "element.h"

/**
 * @brief This class is the graphical representation of a game Element.
 */
class ElementItem : public QGraphicsSvgItem
{

    Q_OBJECT

private:
    /** The Label containing the points won when eaten, to display on the scene */
    QGraphicsTextItem *m_pointsToDisplay = nullptr;

protected:

    /** The instance of Element the ElementItem will represent */
    Element *m_model = nullptr;

public:

    /**
     * Creates a new ElementItem instance.
     * @param p_model the Element model
     */
    explicit ElementItem(Element *p_model);

    /**
     * Deletes the ElementItem instance.
     */
    ~ElementItem() override;

    /**
     * Gets the Element model.
     * @return the model
     */
    Element *getModel() const;

    /**
     * Reimplement QGraphicsItem::shape() to return an ellipse to improve collisions.
     */
    QPainterPath shape() const override;

public Q_SLOTS:

    /**
     * Updates the ElementItem coordinates.
     * @param p_x the new x-coordinate
     * @param p_y the new y-coordinate
     */
    virtual void update(qreal p_x, qreal p_y);
};

#endif

