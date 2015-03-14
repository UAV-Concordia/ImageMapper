#ifndef IMAGEMAPPER_H
#define IMAGEMAPPER_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include "marker.h"

namespace Ui {
class ImageMapper;
}

/*
 * Main application frame
 */
class ImageMapper : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageMapper(QWidget *parent = 0);
    ~ImageMapper();

public slots:
    void redrawMap();
    void zoomIn();
    void zoomOut();

private:
    Ui::ImageMapper *ui;
    QTimer          *updateMap;
    Marker          *uav;
    QGraphicsScene  *scene;
};

#endif // IMAGEMAPPER_H
