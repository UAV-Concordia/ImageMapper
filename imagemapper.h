#ifndef IMAGEMAPPER_H
#define IMAGEMAPPER_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QList>
#include <QTime>
#include "previewdialog.h"
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
    void on_actionCamera_view_triggered();

    void on_actionPreferences_triggered();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_listWidget_itemSelectionChanged();

private:
    void animate(); //fake function for testing

    bool isCaptureTimeExceeded();
    void captureFrame(QImage &frame, QString filename);
    void writeMetadata(MPConnector::MPData &data, QString filename);
    void displayFrame(QImage &frame);
    void moveUAV(qreal x, qreal y);

    QString detectBarcode(QImage &frame);

    // Widgets
    Ui::ImageMapper *ui;
    QTimer          *updateTimer;
    Marker          *uav;
    QGraphicsScene  *scene;
    PreviewDialog   *liveView;

    // Utils
    Camera          *camera;
    MPConnector     *missionPlanner;

    // Properties
    QString destinationFolder;
    int     feedRate;
    int     captureRate;
    QTime   lastCapture;
    QList<QListWidgetItem*> selectedImages;
};

#endif // IMAGEMAPPER_H
