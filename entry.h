#ifndef ENTRY_H
#define ENTRY_H

#include <QString>
#include <QList>
#include "entrymediator.h"

class Entry :public EntryMediator
{
public:
    Entry(QString &path);
    ~Entry();
    bool selected();
    void setSelected(bool state);
    QString path();
    double x();
    double y();
    void setPosition(double x, double y);
    virtual void registerGraphic(QAbstractGraphicsShapeItem *item);
    virtual void registerItem(QTableWidgetItem *item);
    virtual void mark(Qt::CheckState state);
    virtual void show();
private:
    bool state;
    QString _path;
    double _x, _y;
    QTableWidgetItem *tItem;
    QAbstractGraphicsShapeItem *gItem;
};

#endif // ENTRY_H
