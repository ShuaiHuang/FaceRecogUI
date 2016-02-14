#include "FaceRecognitionView.h"
#include "ui_facerecognition.h"

#include <QMessageBox>

FaceRecognition::FaceRecognition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FaceRecognition),
    faceRegistrationPtr(nullptr)
{
    ui->setupUi(this);
    faceRecognitionCtrlPtr = make_shared<FaceRecognitionCtrl>();
    faceRecognitionCtrlPtr->loadOptions();
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
        faceRegistrationPtr = make_unique<FaceRegistration>(this);
    }
    faceRegistrationPtr->setModal(true);
    faceRegistrationPtr->show();
}
