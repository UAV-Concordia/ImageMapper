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

private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_listWidget_itemSelectionChanged();
    void on_actionExport_triggered();

    void on_actionLoad_triggered();

private:
    QString detectBarcode(QImage &frame);

    // Widgets
    Ui::ImageMapper *ui;
    QTimer          *updateTimer;
    Marker          *uav;
    QGraphicsScene  *scene;

    // Properties
    QString destinationFolder;
    QList<QListWidgetItem*> selectedImages;
};

#endif // IMAGEMAPPER_H
