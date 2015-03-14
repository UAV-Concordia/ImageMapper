#include "marker.h"
#include <QPen>

Marker::Marker(QBrush brush, QObject *parent) : QObject(parent), QGraphicsRectItem(0,0,5,5)
{
    this->setPen(QPen(Qt::NoPen));
    this->setBrush(brush);
}

Marker::~Marker()
{

}

