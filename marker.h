#ifndef MARKER_H
#define MARKER_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>

/**
 * Show a little square in the map.
 * This is meant as marker to display elements into the map view.
 */
class Marker : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Marker(QBrush brush = QBrush(Qt::red), QObject *parent = 0);
    ~Marker();
};

#endif // MARKER_H
