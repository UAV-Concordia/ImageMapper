#include "imagemapper.h"
#include "ui_imagemapper.h"
#include <QFileDialog>
#include <QLabel>
#include <QListWidgetItem>
#include <cstdlib>

#include "previewdialog.h"
#include "captureitem.h"
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
    delete uav;
    for (int i = 0; i < ui->listWidget->count(); ++i)
        delete ui->listWidget->item(i);
    delete ui;
}

// Show selected picture (double click)
void ImageMapper::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QImage image(index.data().toString());
    PreviewDialog preview(this);
    preview.setImage(image);
    preview.exec();
}

// Update list selection
void ImageMapper::on_listWidget_itemSelectionChanged()
{
    QList<QListWidgetItem*> newSelection = ui->listWidget->selectedItems();
    foreach (QListWidgetItem* t, selectedImages) {
        if(!newSelection.contains(t)){
            CaptureItem* it = dynamic_cast<CaptureItem*> (t);
            if(it) it->select(false);
        }
    }
    selectedImages = newSelection;
    foreach (QListWidgetItem* t, selectedImages) {
        CaptureItem* it = dynamic_cast<CaptureItem*> (t);
        if(it) it->select(true);
    }
}

// Export option
void ImageMapper::on_actionExport_triggered()
{
    QString dest = QFileDialog::getExistingDirectory(this);
    if(!dest.isEmpty()){
        QTextStream ss(&dest);
        foreach (QListWidgetItem* li, selectedImages) {
            CaptureItem *it = dynamic_cast<CaptureItem*>(li);
            if(it){
                ss << it->fileName() << ","
                   << it->latitude() << ","
                   << it->longitude() << ","
                   << it->altitude();
                endl(ss);
                QFile::copy(it->fileName(), QString(dest).append(it->fileName()));
            }
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
    qDebug() <<gps;
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

    double scale_factor = 1000.0; // TODO: zoom factor

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
        QString sp("/"); // TODO: is because are you using Mac?
        QString rel_image_path = cells.at(0);
        int idx = rel_image_path.indexOf(sp);
        QStringRef filename(&rel_image_path, idx, rel_image_path.length() - idx );
        QStringRef dir(&csv_path, 0, csv_path.lastIndexOf("\\"));
        QString abs_image_path = dir.toString() + filename.toString();
        qDebug() << abs_image_path;

        QString y_coordinate = cells.at(1);
        QString x_coordinate = cells.at(2);
        CaptureItem *m = new CaptureItem(abs_image_path);
        m->setPos(GPSSystem(x_coordinate) *scale_factor, GPSSystem(y_coordinate) *scale_factor);
        this->scene->addItem(m);
        ui->listWidget->insertItem(ui->listWidget->count(), m);
    }
    csv.close();
}
