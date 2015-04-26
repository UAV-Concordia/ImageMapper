#ifndef ENTRYTABLEITEM_H
#define ENTRYTABLEITEM_H

#include <QTableWidgetItem>
#include "entrymediator.h"

class EntryTableItem : public QTableWidgetItem
{
public:
    EntryTableItem(QString &text, EntryMediator *mediator);
    ~EntryTableItem();
    void setCheckState(Qt::CheckState state);
    void show();

private:
    EntryMediator *m;
};

#endif // ENTRYTABLEITEM_H
