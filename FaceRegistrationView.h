#ifndef FACEREGISTRATIONVIEW_H
#define FACEREGISTRATIONVIEW_H

#include <QDialog>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

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

    void on_startPauseButton_clicked();

private:
    Ui::FaceRegistration *ui;
    bool isCameraPaused;
};

#endif // FACEREGISTRATIONVIEW_H
