#include "imagemapper.h"
#include "ui_imagemapper.h"
#include <QFileDialog>
#include <iostream>

ImageMapper::ImageMapper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageMapper)
{
    ui->setupUi(this);

    // Graphics Scene
    this->scene = new QGraphicsScene(this);
    this->uav = new Marker(QBrush(Qt::green));
    this->uav->setZValue(1);
    this->scene->addItem(this->uav);
    ui->graphicsView->setScene(this->scene);

    this->updateTimer = new QTimer();

    // Callbacks
    connect(this->updateTimer, SIGNAL(timeout()), this, SLOT(redrawMap()));

    // Start timer
    this->updateTimer->setSingleShot(true);
    this->updateTimer->start(captureRate());



}

ImageMapper::~ImageMapper()
{
    delete ui;
    delete uav;
}

int ImageMapper::captureRate(){
    int fps = ui->spinBox->value();
    return 1000/fps;
}

// Redraw map called by the timer
void ImageMapper::redrawMap(){
    animate();

    // --------------------------------------------
    // TODO: Get position from Mission Planer

    if(ui->captureButton->isChecked()){
        // TODO:
        // Grab frame
        // Save it to disk
        // Attach metadata

        // Create and insert a new marker into scene
    }
    this->updateTimer->start(captureRate());
}

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

    if(ui->captureButton->isChecked()){
        Marker *m = new Marker();
        m->setPos(pos);
        this->scene->addItem(m);
    }
}

void ImageMapper::on_actionDestination_Folder_triggered(){
    QString dest = QFileDialog::getExistingDirectory();
    if(!dest.isEmpty())
        this->destinationFolder = dest;
}
