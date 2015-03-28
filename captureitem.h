#ifndef CAPTUREITEM_H
#define CAPTUREITEM_H

#include <QListWidgetItem>
#include <QObject>
#include <QImage>
#include <QGraphicsSceneHoverEvent>
#include "marker.h"

/**
 * Capture data container
 */
class CaptureItem : public QListWidgetItem, public Marker
{

public:
    explicit CaptureItem(QString filename, QListWidget *parent = 0);
    ~CaptureItem();

    qreal latitude();
    qreal longitude();
    qreal altitude();
    qreal focalLength();
    qreal pixelSizeX();
    qreal pixelSizeY();
    QString barcode();
    QString fileName();
    QImage image();

    void setLatitude(qreal lat);
    void setLongitude(qreal log);
    void setAltitude(qreal alt);
    void setFocalLength(qreal fl);
    void setPixelSizeX(qreal x, qreal y);
    void setBarcode(QString barcode);

    void select();
    void select(bool mark);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    bool selected;
    qreal _latitude;
    qreal _longitude;
    qreal _altitude;
    qreal _focalLength;
    qreal _pixelSizeX;
    qreal _pixelSizeY;
    QString _barcode;
    QString _fileName;
};

#endif // CAPTUREITEM_H
