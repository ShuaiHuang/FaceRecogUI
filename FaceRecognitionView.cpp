#include "FaceRecognitionView.h"
#include "ui_facerecognition.h"

FaceRecognition::FaceRecognition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FaceRecognition),
    faceRegistrationPtr(nullptr)
{
    ui->setupUi(this);
    faceRecognitionCtrlPtr = make_shared<FaceRecognitionCtrl>();
    faceRecognitionCtrlPtr->loadOptions();

    ui->nextFrameButton->setEnabled(false);
    ui->faceIndComboBox->setEnabled(false);
    ui->recogButton->setEnabled(false);
    ui->stopRecogButton->setEnabled(false);
}

FaceRecognition::~FaceRecognition()
{
    delete ui;
}

void FaceRecognition::on_actionQuit_triggered()
{
    qApp->exit();
}

void FaceRecognition::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", "Made by Shuai Huang, PAMI Lab");
}

void FaceRecognition::on_actionRegister_Face_triggered()
{
    if (faceRegistrationPtr == nullptr)
    {
        faceRegistrationPtr = make_shared<FaceRegistration>(this);
        faceRegistrationPtr->setModal(true);
        connect(
                    this,
                    &FaceRecognition::sendFaceRecognitionCtrlPtr,
                    faceRegistrationPtr.get(),
                    &FaceRegistration::receiveFaceRecognitionCtrlPtr);
    }
    emit sendFaceRecognitionCtrlPtr(faceRecognitionCtrlPtr);
    faceRegistrationPtr->show();
}

void FaceRecognition::on_loadVideoButton_clicked()
{
    QString videoFile = QFileDialog::getOpenFileName(this, "Open Video File", ".", "Video (*.avi)");
    if (!videoFile.isEmpty())
    {
        faceRecognitionCtrlPtr->loadVideo(videoFile);
    }
}
