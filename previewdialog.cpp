#include "previewdialog.h"
#include "ui_previewdialog.h"
#include <QPixmap>

PreviewDialog::PreviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);
    this->setModal(false);
}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}

void PreviewDialog::setImage(QImage &image){
    ui->label->setPixmap(QPixmap::fromImage(image));
}
