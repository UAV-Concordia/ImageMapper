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

    /**
     * Set the device index to use for capture
     * The index should be between 0 and maxVideoDevices
     * @param dev index
     */
    void setCurrentDevice(int dev);

    /**
     * Set the maximum index allowed for the spinbox
     * @param maxVideoDevices
     */
    void setNumberDevices(int maxVideoDevices);

    /**
     * Retrive the selected device.
     * @return device index
     */
    int selectedDeviceIndex();

private:
    Ui::CaptureDeviceDialog *ui;
};

#endif // CAPTUREDEVICEDIALOG_H
