#include "captureitem.h"
#include <QColor>
#include <QPen>
#include "previewdialog.h"
#include <QDebug>

CaptureItem::CaptureItem(QString filename, QListWidget *parent):
    QListWidgetItem(filename, parent),
    selected(false),
    _fileName(filename)
{}

CaptureItem::~CaptureItem(){ }

qreal CaptureItem::latitude() { return this->_latitude; }
qreal CaptureItem::longitude() { return this->_longitude; }
qreal CaptureItem::altitude() { return this->_altitude; }
qreal CaptureItem::focalLength() { return this->_focalLength; }
qreal CaptureItem::pixelSizeX() { return this->_pixelSizeX; }
qreal CaptureItem::pixelSizeY() { return this->_pixelSizeY; }
QString CaptureItem::barcode(){ return this->_barcode; }
QString CaptureItem::fileName(){ return this->_fileName; }
QImage CaptureItem::image() { return QImage(this->_fileName); }

void CaptureItem::setLatitude(qreal lat) { this->_latitude = lat; }
void CaptureItem::setLongitude(qreal log){ this->_longitude = log; }
void CaptureItem::setAltitude(qreal alt) { this->_altitude = alt; }
void CaptureItem::setFocalLength(qreal fl) { this->_focalLength = fl; }
void CaptureItem::setPixelSizeX(qreal x, qreal y) { this->_pixelSizeX = x; this->_pixelSizeY = y; }
void CaptureItem::setBarcode(QString barcode) { this->_barcode = barcode; setTextColor(QColor(238,170,0));}

void CaptureItem::select(){
    select(!selected);
}

void CaptureItem::select(bool mark){
    if(mark != selected){
        selected = !selected;
        (selected)?setPen(QPen(QColor(Qt::black))):setPen(Qt::NoPen);
    }
}

void CaptureItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    qDebug() << "trigged";
    if(event->modifiers() & Qt::ShiftModifier) select(true);
}

void CaptureItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->select(!selected);
}

void CaptureItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    PreviewDialog dlg;
    dlg.setImage(image());
    dlg.exec();
}
