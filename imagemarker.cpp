#include "imagemarker.h"
#include <QGraphicsSceneHoverEvent>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPen>
#include "previewdialog.h"

ImageMarker::ImageMarker(QString filepath)
{
    this->pictureFile = filepath;
    this->setAcceptHoverEvents(true);
    this->selected = false;
}

ImageMarker::~ImageMarker()
{

}

void ImageMarker::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    if(!this->selected && (event->modifiers() & Qt::ShiftModifier)){
        select();
    }
}

void ImageMarker::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(this->selected)
        deselect();
    else
        select();
}

void ImageMarker::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    QImage img (this->pictureFile);
    PreviewDialog dlg;
    dlg.setImage(img);
    dlg.exec();
}


void ImageMarker::select(){
    this->setPen(QPen(Qt::black));
    this->selected = true;
}
void ImageMarker::deselect(){
    this->setPen(QPen(Qt::NoPen));
    this->selected = false;
}

QString ImageMarker::imagePath(){
    return this->pictureFile;
}
