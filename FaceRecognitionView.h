#ifndef FACERECOGNITIONVIEW_H
#define FACERECOGNITIONVIEW_H

#include <QMainWindow>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/face.hpp>
#include <opencv2/tracking.hpp>

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
    FaceRecognitionCtrl faceRecognitionCtrl;
};

#endif // FACERECOGNITIONVIEW_H
