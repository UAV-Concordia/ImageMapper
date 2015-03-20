#ifndef CAPTUREDEVICEDIALOG_H
#define CAPTUREDEVICEDIALOG_H

#include <QDialog>

/**
 * Dialog to select capturing device
 */
namespace Ui {
class CaptureDeviceDialog;
}

class CaptureDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CaptureDeviceDialog(QWidget *parent = 0);
    ~CaptureDeviceDialog();
    void setCurrentDevice(int dev);
    void setNumberDevices(int maxVideoDevices);
    int selectedDeviceIndex();

private:
    Ui::CaptureDeviceDialog *ui;
};

#endif // CAPTUREDEVICEDIALOG_H
