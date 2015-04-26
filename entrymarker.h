#ifndef MARKER_H
#define MARKER_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include "entrymediator.h"

/**
 * Show a little square in the map.
 * This is meant as marker to display elements into the map view.
 */
class EntryMarker : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit EntryMarker(EntryMediator *mediator, QObject *parent = 0);
    virtual ~EntryMarker();

    //virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    EntryMediator *m;
};

#endif // MARKER_H
