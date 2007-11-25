#include "gameview.h"

GameView::GameView(QGraphicsScene* p_scene) : QGraphicsView(p_scene) {

}

GameView::~GameView() {

}

void GameView::resizeEvent(QResizeEvent* p_event) {
	// Resize the scene to fit in the viewport
	fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void GameView::keyPressEvent(QKeyEvent* p_event) {
	emit(keyPressed(p_event));
}
