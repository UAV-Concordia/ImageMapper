#include "capturedevicedialog.h"
#include "ui_capturedevicedialog.h"

CaptureDeviceDialog::CaptureDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaptureDeviceDialog)
{
    ui->setupUi(this);
}

CaptureDeviceDialog::~CaptureDeviceDialog()
{
    delete ui;
}

void CaptureDeviceDialog::setCurrentDevice(int id){
    ui->spinBox->setValue(id);
}

void CaptureDeviceDialog::setNumberDevices(int maxVideoDevices){
    ui->spinBox->setMaximum(maxVideoDevices);
}

int CaptureDeviceDialog::selectedDeviceIndex(){
    return ui->spinBox->value();
}
