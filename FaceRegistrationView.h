#ifndef FACEREGISTRATIONVIEW_H
#define FACEREGISTRATIONVIEW_H

#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsPixmapItem>

#include "faceregistrationctrl.h"
#include "facerecognitionctrl.h"

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

    void on_regButton_clicked();

    void on_FaceRegistration_rejected();

public slots:
    void receiveFaceRecognitionCtrlPtr(shared_ptr<FaceRecognitionCtrl> _faceRecognitionCtrlPtr);

private:
    Ui::FaceRegistration *ui;
    shared_ptr<FaceRecognitionCtrl> faceRecognitionCtrlPtr;
    shared_ptr<FaceRegistrationCtrl> faceRegistrationCtrlPtr;
    bool isCameraPaused;
};

#endif // FACEREGISTRATIONVIEW_H
