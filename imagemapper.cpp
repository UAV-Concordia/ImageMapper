#include "imagemapper.h"
#include "ui_imagemapper.h"
#include <QFileDialog>
#include <QLabel>
#include <QListWidgetItem>
#include <cstdlib>

#include "preferencesdialog.h"
#include "previewdialog.h"
#include "captureitem.h"

#include <QDebug>

#define FPS(ms) (2000.0/(ms))
#define MS(fps) (2000.0/(fps))

ImageMapper::ImageMapper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageMapper),
    captureRate(MS(1)),
    feedRate(MS(4))
{
    ui->setupUi(this);

    // Mission Planner
    missionPlanner = new MPConnector();
    missionPlanner->connect("localhost", 49000);

    // Camera
    this->camera = new Camera();
    camera->setDevice(0);

    // Live view
    liveView = new PreviewDialog(this);

    // Graphics Scene
    this->scene = new QGraphicsScene(this);
    // UAV Marker
    this->uav = new Marker(QBrush(Qt::green));
    this->uav->setZValue(1);
    this->scene->addItem(this->uav);
    ui->graphicsView->setScene(this->scene);

    // Refresh
    this->updateTimer = new QTimer();
    connect(this->updateTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    this->updateTimer->setSingleShot(true);
    this->updateTimer->start(captureRate);
    lastCapture.start();
}

ImageMapper::~ImageMapper()
{
    delete uav;
    delete camera;
    delete missionPlanner;
    delete liveView;
    for (int i = 0; i < ui->listWidget->count(); ++i)
        delete ui->listWidget->item(i);
    delete ui;
}

bool ImageMapper::isCaptureTimeExceeded(){
    if(lastCapture.elapsed() > captureRate){
        this->lastCapture.restart();
        return true;
    }
    return false;
}

void ImageMapper::captureFrame(QImage &frame, QString filename){
    if(frame.isNull()) frame = camera->getFrame();
    frame.save(filename, "JPG");
}

void ImageMapper::writeMetadata(MPConnector::MPData &data, QString filename){
    // TODO: Write XML for PIX4D
}

QString ImageMapper::detectBarcode(QImage &frame){
    // TODO: Detect barcode, on error return empty string
    return QString();
}

void ImageMapper::displayFrame(QImage &frame){
    if(frame.isNull()) frame = camera->getFrame();
    liveView->setImage(frame);
}

void ImageMapper::moveUAV(qreal x, qreal y){
    this->uav->setPos(x, y);
}

void ImageMapper::refresh(){
    animate(); // This is for test will be deleted

    // --------------------------------------------

    QImage              frame;
    MPConnector::MPData data;
    //MPConnector::MPData data = missionPlanner->getData();
    //moveUAV(data.longitude, data.latitude);

    // Capture
    if(ui->captureButton->isChecked() && isCaptureTimeExceeded()){
        // Name
        QString filename = QString("%1/%2.jpg").arg(this->destinationFolder).arg(rand());
        captureFrame(frame, filename);


        QString barcode = detectBarcode(frame);


        // Create and insert a new capture record
        CaptureItem *item = new CaptureItem(filename);
        item->setPos(QPoint(rand()/1000, rand()/1000));
        //item->setPos(QPoint(data.longitude, data.latitude));
        this->scene->addItem(item);
        ui->listWidget->insertItem(ui->listWidget->count(), item);
        //writeMetadata(data, filename);
    }

    // Viewer
    if(!liveView->isHidden()){
        displayFrame(frame);
    }

    this->updateTimer->start(feedRate);
}

// TODO: Remove
void ImageMapper::animate(){
    // Test Animation -- loop
    QPointF pos = this->uav->pos();

    // Corners
    if(pos.x() == 0 && pos.y() == 0){
        this->uav->setPos(0, 10);
    }
    else if(pos.x() == 0 && pos.y() == 100){
        this->uav->setPos(10, 100);
    }
    else if(pos.x() == 100 && pos.y() == 100){
        this->uav->setPos(100, 90);
    }
    else if(pos.x() == 100 && pos.y() == 0){
        this->uav->setPos(90, 0);
    }
    // Edges
    else if(pos.x() == 0 && pos.y() > 0){
        this->uav->setPos(0, pos.y() + 10);
    }
    else if(pos.x() > 0 && pos.y() == 100){
        this->uav->setPos(pos.x() + 10, 100);
    }
    else if(pos.x() == 100 && pos.y() < 100){
        this->uav->setPos(100, pos.y() - 10);
    }
    else if(pos.x() < 100 && pos.y() == 0){
        this->uav->setPos(pos.x() - 10, 0);
    }

//    if(ui->captureButton->isChecked()){
//        Marker *m = new ImageMarker("No image");
//        m->setPos(pos);
//        this->scene->addItem(m);
//    }
}

void ImageMapper::on_actionCamera_view_triggered()
{
    liveView->show();
}

void ImageMapper::on_actionPreferences_triggered()
{
    PreferencesDialog pref;
    // Setup
    pref.setDestinationFolder(this->destinationFolder);
    pref.setMaxDeviceIndex(camera->getDevices());
    pref.setFeedRate(FPS(this->feedRate));
    pref.setCaptureRate(FPS(this->captureRate));

    if(pref.exec() == QDialog::Accepted){
        this->destinationFolder = pref.getDestinationFolder();
        this->camera->setDevice(pref.getDeviceIndex());
        this->captureRate = MS(pref.getCaptureRate());
        this->feedRate    = MS(pref.getFeedRate());
    }
}

void ImageMapper::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QImage image(index.data().toString());
    PreviewDialog preview(this);
    preview.setImage(image);
    preview.exec();
}

void ImageMapper::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem*> newSelection = ui->listWidget->selectedItems();
    foreach (QListWidgetItem* t, selectedImages) {
        if(!newSelection.contains(t)){
            CaptureItem* it = dynamic_cast<CaptureItem*> (t);
            if(it) it->select(false);
        }
    }
    selectedImages = newSelection;
    foreach (QListWidgetItem* t, selectedImages) {
        CaptureItem* it = dynamic_cast<CaptureItem*> (t);
        if(it) it->select(true);
    }
}
