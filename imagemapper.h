#ifndef IMAGEMAPPER_H
#define IMAGEMAPPER_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include "marker.h"
#include "mapview.h"

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

private:
    void animate(); //fake function for testing

    int captureRate();

    Ui::ImageMapper *ui;
    QTimer          *updateTimer;
    Marker          *uav;
    QGraphicsScene  *scene;
};

#endif // IMAGEMAPPER_H
