#include "entry.h"
#include <QDebug>
#include <QPen>
#include "previewdialog.h"

Entry::Entry(QString &path):
    _path(path)
{}

Entry::~Entry()
{}

// Selected state
bool Entry::selected(){
    return this->state;
}

void Entry::setSelected(bool state){
    if(this->state != state){
        this->state = state;
        if(state){
            this->tItem->setCheckState(Qt::Checked);
            this->gItem->setPen(QPen(QColor(0,0,0)));
        }
        else{
            this->tItem->setCheckState(Qt::Unchecked);
            this->gItem->setPen(Qt::NoPen);
        }
    }
}

// File path
QString Entry::path(){
    return this->_path;
}

// Coordinates
double Entry::x(){
    return this->_x;
}

double Entry::y(){
    return this->_y;
}

// Rescale position of graphic widget
// FIXME: compasate for wrapping
static double rescale(double a){
    long int b = (long int) (a * 10000);
    return (double) (b % 1000);
}

void Entry::setPosition(double x, double y){
    this->_x=x;
    this->_y=y;
    this->gItem->setPos(rescale(x), rescale(y));
}

// Mediator
// Table item
void Entry::registerItem(QTableWidgetItem *item){
    this->tItem = item;
}

// Graphic marker
void Entry::registerGraphic(QAbstractGraphicsShapeItem *item){
    this->gItem = item;
}

// Mark for export
void Entry::mark(Qt::CheckState state){
    if(state == Qt::Checked)
        this->setSelected(true);
    else
        this->setSelected(false);
}

// Show preview dialog
void Entry::show(){
    QImage image(this->path());
    QImage image2 =image.scaled(640.0,480.0, Qt::KeepAspectRatio);
    PreviewDialog preview;
    preview.setImage(image2);
    preview.exec();
}
