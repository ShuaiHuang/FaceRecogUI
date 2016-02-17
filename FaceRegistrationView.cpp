#include "FaceRegistrationView.h"
#include "ui_faceregistration.h"

//#include "FaceRecognitionView.h"

FaceRegistration::FaceRegistration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceRegistration)
{
    ui->setupUi(this);
    faceRegistrationCtrlPtr = nullptr;
    isCameraPaused = true;
}

FaceRegistration::~FaceRegistration()
{
    delete ui;
}

void FaceRegistration::on_loadImgButton_clicked()
{
    QString imageFile = QFileDialog::getOpenFileName(this, "Open Image File", ".", "Images (*.png *.bmp *.jpg)");
    if (imageFile.size() != 0)
    {
        faceRegistrationCtrlPtr->loadImage(IMAGE_FROM_FILE, imageFile);
        QImage dstImg;
        faceRegistrationCtrlPtr->detectFaces(dstImg);
        if (dstImg.width() > 340)
        {
            dstImg = dstImg.scaled(340, 260, Qt::KeepAspectRatio);
        }
        ui->dstImageView->setPixmap(QPixmap::fromImage(dstImg));
    }
}

void FaceRegistration::on_imgRadioButton_toggled(bool checked)
{
    ui->loadImgButton->setEnabled(checked);
}

void FaceRegistration::on_cameraRadioButton_toggled(bool checked)
{
//    ui->startPauseButton->setEnabled(checked);
//    if (!checked)
//    {
//        isCameraPaused = true;
//        ui->startPauseButton->setText("Start");
//    }
}

void FaceRegistration::on_startPauseButton_clicked()
{
    isCameraPaused = !isCameraPaused;
    if (isCameraPaused)
    {
        ui->startPauseButton->setText("Start");
    }
    else
    {
        ui->startPauseButton->setText("Pause");
    }
}

void FaceRegistration::receiveFaceRecognitionCtrlPtr(shared_ptr<FaceRecognitionCtrl> _faceRecognitionCtrlPtr)
{
    faceRecognitionCtrlPtr = _faceRecognitionCtrlPtr;
    Ptr<FaceRecognizer> faceRecognizerPtr;
    faceRecognitionCtrlPtr->getFaceRecognizer(faceRecognizerPtr);
    faceRegistrationCtrlPtr = make_shared<FaceRegistrationCtrl>(faceRecognizerPtr);
}
