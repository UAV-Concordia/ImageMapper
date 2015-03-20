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

/**
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

private slots:
    void on_actionDestination_Folder_triggered();

    void on_actionCapture_device_triggered();

private:
    void animate(); //fake function for testing

    /**
     * Get the delay for next capture
     * @return millisecond to next capture
     */
    int captureRate();

    Ui::ImageMapper *ui;
    QTimer          *updateTimer;
    Marker          *uav;
    QGraphicsScene  *scene;
    QString         destinationFolder;
};

#endif // IMAGEMAPPER_H
