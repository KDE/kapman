#ifndef __KAPMANVIEW_H
#define __KAPMANVIEW_H

#include <QGraphicsSvgItem>
#include <QString>
#include "kapman.h"

/**
 * This class is the graphical representation of the main character
 */
class KapmanView : public QGraphicsSvgItem {

	Q_OBJECT

	public:

		/**
		 * Creates a new KapmanView instance
		 * @param p_model the Kapman model
		 * @param p_imagePath the Kapman image path
		 */
		KapmanView(Kapman* p_model, QString p_imagePath);

		/**
		 * Deletes the KapmanView instance
		 */
		~KapmanView();

	public slots:

		/**
		 * Updates the view coordinates
		 * @param p_x the new x-coordinate
		 * @param p_y the new y-coordinate
		 */
		void update(int p_x, int p_y);
};

#endif
