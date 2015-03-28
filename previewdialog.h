#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
#include <QImage>

namespace Ui {
class PreviewDialog;
}

/**
 * Show an image in a modeless window.
 */
class PreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviewDialog(QWidget *parent = 0);
    ~PreviewDialog();

public slots:
    void setImage(QImage &image);

private:
    Ui::PreviewDialog *ui;
};

#endif // PREVIEWDIALOG_H
