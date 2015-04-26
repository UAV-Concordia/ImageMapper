#ifndef IMAGEMAPPER_H
#define IMAGEMAPPER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include "previewdialog.h"
#include "entry.h"
#include "entrymarker.h"
#include "entrytableitem.h"
#include "mapview.h"

namespace Ui {
class ImageMapper;
}

/**
 * Main application frame
 */
class ImageMapper : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageMapper(QWidget *parent = 0);
    ~ImageMapper();
    Entry* createEntry(QString &image);

private slots:
    void on_actionExport_triggered();
    void on_actionLoad_triggered();\
    void on_tableWidget_itemChanged(QTableWidgetItem *item);
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

private:
    // Widgets
    Ui::ImageMapper *ui;
    QGraphicsScene  *scene;
    QList<Entry*> entries;
};

#endif // IMAGEMAPPER_H
