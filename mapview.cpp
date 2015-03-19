#include "mapview.h"

MapView::MapView(QWidget *parent):
    QGraphicsView(parent)
{}

MapView::~MapView(){}

void MapView::wheelEvent(QWheelEvent *event){
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

