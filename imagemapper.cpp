#include "imagemapper.h"
#include "ui_imagemapper.h"

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

    this->updateMap = new QTimer();

    // Callbacks
    connect(this->updateMap, SIGNAL(timeout()), this, SLOT(redrawMap()));

    // Zooming
    // This should reimplement the GraphicsView to use the wheel
    QAction *zoomInAction = new QAction(this);
    QAction *zoomOutAction = new QAction(this);
    zoomInAction->setShortcut(Qt::Key_Plus | Qt::CTRL);
    zoomOutAction->setShortcut(Qt::Key_Minus | Qt::CTRL);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
    this->addAction(zoomInAction);
    this->addAction(zoomOutAction);

    // Start timer
    this->updateMap->start(100);
}

ImageMapper::~ImageMapper()
{
    delete ui;
    delete uav;
}

// Zoom callback test
void ImageMapper::zoomIn(){
    ui->graphicsView->scale(1.2, 1.2);
}
void ImageMapper::zoomOut(){
    ui->graphicsView->scale(0.8, 0.8);
}

// Redraw map called by the timer
void ImageMapper::redrawMap(){
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


    // --------------------------------------------
    // TODO: Get position from Mission Planer

    if(ui->captureButton->isChecked()){
        // TODO:
        // Grab frame
        // Save it to disk
        // Attach metadata

        // Create and insert a new marker into scene
    }
}
