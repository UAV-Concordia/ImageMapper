#include "entrytableitem.h"
#include <QDebug>

EntryTableItem::EntryTableItem(QString &text, EntryMediator *mediator):
    QTableWidgetItem(text),
    m(mediator)
{
    QTableWidgetItem::setCheckState(Qt::Unchecked);
    m->registerItem(this);
}

EntryTableItem::~EntryTableItem()
{

}

void EntryTableItem::setCheckState(Qt::CheckState state){
    //if(state != this->checkState()){
        QTableWidgetItem::setCheckState(state);
        m->mark(state);
    //}
}


void EntryTableItem::show(){
    m->show();
}
