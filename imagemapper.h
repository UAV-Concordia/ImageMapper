#ifndef IMAGEMAPPER_H
#define IMAGEMAPPER_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QGraphicsScene>
#include <QDialog>
#include "mpconnector.h"
#include "marker.h"
#include "mapview.h"
#include "camera.h"

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
    void refresh();

private slots:
    void on_actionDestination_Folder_triggered();

    void on_actionCapture_device_triggered();

    void on_actionCamera_view_triggered();

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
    QLabel          *liveFeed;
    QDialog         *liveView;
    Camera          *camera;
    MPConnector     *missionPlanner;
};

#endif // IMAGEMAPPER_H
