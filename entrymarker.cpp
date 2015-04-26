#include "entrymarker.h"
#include <QPen>
#include <QDebug>

EntryMarker::EntryMarker(EntryMediator *mediator, QObject *parent):
    QObject(parent),
    QGraphicsEllipseItem(0,0,5,5),
    m(mediator)
{
    this->setPen(QPen(Qt::NoPen));
    this->setBrush(QBrush(Qt::red));
    m->registerGraphic(this);
}

EntryMarker::~EntryMarker()
{}

void EntryMarker::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    m->show();
}
