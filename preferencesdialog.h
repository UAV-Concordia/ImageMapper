#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();

    QString getDestinationFolder();
    int     getDeviceIndex();
    int     getFeedRate();
    int     getCaptureRate();

    void setDestinationFolder(QString dir);
    void setMaxDeviceIndex(int max);
    void setFeedRate(int rate);
    void setCaptureRate(int rate);

private slots:
    void on_selectDirectoryButton_clicked();
    void on_feedRateSpinBox_valueChanged(int rate);

private:
    Ui::PreferencesDialog *ui;
};

#endif // PREFERENCESDIALOG_H
