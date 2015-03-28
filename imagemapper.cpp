#include "imagemapper.h"
#include "ui_imagemapper.h"
#include <QFileDialog>
#include <iostream>
#include <QLabel>
#include "capturedevicedialog.h"
#include "imagemarker.h"
#include <cstdlib>

ImageMapper::ImageMapper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageMapper)
{
    ui->setupUi(this);

    // Mission Planner
    missionPlanner = new MPConnector();
    missionPlanner->connect("localhost", 49000);

    // Camera
    this->camera = new Camera();
    camera->setDevice(0);

    // Live view
    liveFeed = new QLabel();
    liveView = new QDialog(this);

    QVBoxLayout *lout = new QVBoxLayout(liveView);
    lout->addWidget(liveFeed);
    liveView->setLayout(lout);
    liveView->resize(420,280);


    // Graphics Scene
    this->scene = new QGraphicsScene(this);
    this->uav = new Marker(QBrush(Qt::green));
    this->uav->setZValue(1);
    this->scene->addItem(this->uav);
    ui->graphicsView->setScene(this->scene);

    this->updateTimer = new QTimer();

    // Callbacks
    connect(this->updateTimer, SIGNAL(timeout()), this, SLOT(refresh()));

    // Start timer
    this->updateTimer->setSingleShot(true);
    this->updateTimer->start(captureRate());

    this->on_actionDestination_Folder_triggered();

}

ImageMapper::~ImageMapper()
{
    delete ui;
    delete uav;
    delete camera;
    delete missionPlanner;
    if(liveFeed != NULL)
        delete liveFeed;
}

int ImageMapper::captureRate(){
    int fps = ui->spinBox->value();
    return 1000/fps;
}

void ImageMapper::refresh(){
    animate();

    // --------------------------------------------
    // TODO: Get position from Mission Planer
    QImage frame;

    if(ui->captureButton->isChecked()){
        // Grab frame
        frame = this->camera->getFrame();

        // Save it to disk
        QString filename = QString("%1/%2.jpg").arg(this->destinationFolder).arg(rand());
        frame.save(filename, "JPG");
        // Attach metadata
        missionPlanner->setData(filename.toStdString());

        // Create and insert a new marker into scene
        Marker *m = new ImageMarker(filename);
        m->setPos(QPoint(rand()/1000, rand()/1000));
        this->scene->addItem(m);
    }

    if(!liveView->isHidden()){
        if(frame.isNull()) frame = camera->getFrame();
        liveFeed->setPixmap(QPixmap::fromImage(frame));
    }
    this->updateTimer->start(captureRate());
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

void ImageMapper::on_actionDestination_Folder_triggered(){
    QString dest = QFileDialog::getExistingDirectory();
    if(!dest.isEmpty())
        this->destinationFolder = dest;
}

void ImageMapper::on_actionCapture_device_triggered()
{
    CaptureDeviceDialog dlg;
    dlg.setCurrentDevice(0);
    dlg.setNumberDevices(camera->getDevices());
    if(dlg.exec() == QDialog::Accepted){
        camera->setDevice(dlg.selectedDeviceIndex());
    }
}

void ImageMapper::on_actionCamera_view_triggered()
{
    liveView->show();
}
