#ifndef FACERECOGNITIONVIEW_H
#define FACERECOGNITIONVIEW_H

#include <QMainWindow>

#include "facerecognitionctrl.h"
#include "FaceRegistrationView.h"

namespace Ui {
class FaceRecognition;
}

class FaceRecognition : public QMainWindow
{
    Q_OBJECT

public:
    explicit FaceRecognition(QWidget *parent = 0);
    ~FaceRecognition();

private slots:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionRegister_Face_triggered();

private:
    Ui::FaceRecognition *ui;
    shared_ptr<FaceRecognitionCtrl> faceRecognitionCtrlPtr;
    unique_ptr<FaceRegistration> faceRegistrationPtr;
};

#endif // FACERECOGNITIONVIEW_H
