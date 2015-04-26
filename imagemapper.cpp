#include "imagemapper.h"
#include "ui_imagemapper.h"
#include <QFileDialog>
#include <QLabel>
#include <QListWidgetItem>
#include <cstdlib>

#include "previewdialog.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

ImageMapper::ImageMapper(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageMapper)
{
    ui->setupUi(this);

    // Graphics Scene
    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(this->scene);
}

ImageMapper::~ImageMapper()
{
    foreach (Entry *e, entries) {
        delete e;
    }
    delete ui;
}

Entry* ImageMapper::createEntry(QString &image){
    Entry          *entry  = new Entry(image);
    EntryTableItem *item   = new EntryTableItem(image, entry);
    EntryMarker    *marker = new EntryMarker(entry);
    int row = entries.size();
    ui->tableWidget->setRowCount(row+1);
    ui->tableWidget->setItem(row, 0, item);
    scene->addItem(marker);
    entries.append(entry);
    return entry;
}

// Export option
void ImageMapper::on_actionExport_triggered()
{
    QString dest = QFileDialog::getExistingDirectory(this);
    if(!dest.isEmpty()){
        foreach (Entry* entry, entries) {
            QFile::copy(entry->path(), QString(dest).append(entry->path()));
        }
    }
}

// Converting from DMS to GPS coordinate
static double GPSSystem(QString &dms_coordinate){
    // "45 deg 29' 42.35"" N"
    QRegExp rx("(\\d+) deg (\\d+)' (\\d+\\.\\d+)");
    rx.indexIn(dms_coordinate);
    int    deg = rx.cap(1).toInt();
    int    min = rx.cap(2).toInt();
    double sec = rx.cap(3).toDouble();
    double gps = deg + (min/60.0) + (sec / 3600.0);
    qDebug() << gps;
    return gps;
}

// Load option
void ImageMapper::on_actionLoad_triggered()
{
    // Clean up scene
    this->scene->clear();

    /*
     * CSV
     * IMAGE_NAME, x, y
     */
    QString csv_path = QFileDialog::getOpenFileName();
    QFile csv(csv_path);
    csv.open(QIODevice::ReadOnly);

    for(int i = 0; ;i++){
        QByteArray bline = csv.readLine();
        if(bline.isEmpty())
            break;
        QString sline(bline);
        QStringList cells = sline.split(",");
        if(cells.size() != 3){
            qDebug() << "Error parsing line "+i;
            continue;
        }
        // Translate from relative to absolute path
        QString sp("/");
        QString rel_image_path = cells.at(0);
        int idx = rel_image_path.indexOf(sp);
        QStringRef filename(&rel_image_path, idx, rel_image_path.length() - idx );
        QStringRef dir(&csv_path, 0, csv_path.lastIndexOf(sp));
        QString abs_image_path = dir.toString() + filename.toString();
        qDebug() << abs_image_path;
        // Set coordinates
        QString y_coordinate = cells.at(1);
        QString x_coordinate = cells.at(2);
        // Add entry
        Entry *e = createEntry(abs_image_path);
        e->setPosition(GPSSystem(x_coordinate),GPSSystem(y_coordinate));
    }
    csv.close();
}

void ImageMapper::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    EntryTableItem *eItem = dynamic_cast<EntryTableItem*>(item);
    if(eItem->checkState() == Qt::Checked)
        eItem->setCheckState(Qt::Checked);
    else
        eItem->setCheckState(Qt::Unchecked);
}

void ImageMapper::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    EntryTableItem *eItem = dynamic_cast<EntryTableItem*>(item);
    eItem->show();
}
