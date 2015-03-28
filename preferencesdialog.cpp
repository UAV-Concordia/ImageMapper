#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include <QFileDialog>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

QString PreferencesDialog::getDestinationFolder(){ return ui->destinationLabel->text(); }
int PreferencesDialog::getDeviceIndex(){ return ui->deviceIndexSpinBox->value(); }
int PreferencesDialog::getFeedRate(){ return ui->feedRateSpinBox->value(); }
int PreferencesDialog::getCaptureRate(){ return ui->captureRateSpinBox->value(); }

void PreferencesDialog::setDestinationFolder(QString dir) { ui->destinationLabel->setText(dir); }
void PreferencesDialog::setMaxDeviceIndex(int max) { ui->deviceIndexSpinBox->setMaximum(max); }
void PreferencesDialog::setFeedRate(int rate) { ui->feedRateSpinBox->setValue(rate); }
void PreferencesDialog::setCaptureRate(int rate){ ui->captureRateSpinBox->setValue(rate); }

void PreferencesDialog::on_selectDirectoryButton_clicked(){
    QString dest = QFileDialog::getExistingDirectory();
    if(!dest.isEmpty())
        ui->destinationLabel->setText(dest);
}

void PreferencesDialog::on_feedRateSpinBox_valueChanged(int rate){
    ui->captureRateSpinBox->setMaximum(rate);
}
