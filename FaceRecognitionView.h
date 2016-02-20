#ifndef FACERECOGNITIONVIEW_H
#define FACERECOGNITIONVIEW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QImage>

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

    void on_loadVideoButton_clicked();

    void on_nextFrameButton_clicked();

    void on_selectionButton_clicked();

    void on_playButton_clicked();

private:
    Ui::FaceRecognition *ui;
    shared_ptr<FaceRecognitionCtrl> faceRecognitionCtrlPtr;
    shared_ptr<FaceRegistration> faceRegistrationPtr;

signals:
    void sendFaceRecognitionCtrlPtr(shared_ptr<FaceRecognitionCtrl> _faceRecognitionCtrlPtr);
};

#endif // FACERECOGNITIONVIEW_H
