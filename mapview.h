#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QWidget>
#include <QGraphicsView>
#include <QWheelEvent>

/**
 * Map Widget
 */
class MapView : public QGraphicsView
{
public:
    MapView(QWidget *parent = 0);
    ~MapView();
    virtual void wheelEvent(QWheelEvent *event);
};

#endif // MAPVIEW_H
