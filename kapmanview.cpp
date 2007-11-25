#include "kapmanview.h"

KapmanView::KapmanView(Kapman* p_model, QString p_imagePath) :
		QGraphicsSvgItem(p_imagePath) {
	// Init the view coordinates
	setPos(p_model->getX(), p_model->getY());
	// Connect the model to the view
	connect(p_model, SIGNAL(moved(int, int)), this, SLOT(update(int, int)));
}

KapmanView::~KapmanView() {

}

void KapmanView::update(int p_x, int p_y) {
	// Update the view coordinates
	setPos(p_x, p_y);
}
