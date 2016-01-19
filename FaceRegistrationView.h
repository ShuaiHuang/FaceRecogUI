#ifndef FACEREGISTRATIONVIEW_H
#define FACEREGISTRATIONVIEW_H

#include <QDialog>

namespace Ui {
class FaceRegistration;
}

class FaceRegistration : public QDialog
{
    Q_OBJECT

public:
    explicit FaceRegistration(QWidget *parent = 0);
    ~FaceRegistration();

private slots:
    void on_loadImgButton_clicked();
    void on_imgRadioButton_toggled(bool checked);

    void on_cameraRadioButton_toggled(bool checked);

private:
    Ui::FaceRegistration *ui;
};

#endif // FACEREGISTRATIONVIEW_H
