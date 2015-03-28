#ifndef IMAGEMARKER_H
#define IMAGEMARKER_H
#include "marker.h"

/**
 * Marker representing and images
 * this call implements some callbacks for mouse event for selection and preview.
 */
class ImageMarker : public Marker
{
public:
    ImageMarker(QString filepath);
    ~ImageMarker();
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QString imagePath();
private:
    void select();
    void deselect();
    bool selected;
    QString pictureFile;
};

#endif // IMAGEMARKER_H
