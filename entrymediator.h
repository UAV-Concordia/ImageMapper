#ifndef ENTRYMEDIATOR
#define ENTRYMEDIATOR

#include <QAbstractGraphicsShapeItem>
#include <QTableWidgetItem>

class EntryMediator {
public:
    virtual void registerGraphic(QAbstractGraphicsShapeItem *item)=0;
    virtual void registerItem(QTableWidgetItem *item)=0;
    virtual void mark(Qt::CheckState state)=0;
    virtual void show()=0;
};

#endif // ENTRYMEDIATOR

