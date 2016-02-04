#include "FaceRecognitionView.h"
#include "ui_facerecognition.h"

#include <QMessageBox>

FaceRecognition::FaceRecognition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FaceRecognition)
{
    ui->setupUi(this);
    faceRecognitionCtrlPtr = makePtr<FaceRecognitionCtrl>();
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
    FaceRegistration faceReg(this);
    faceReg.exec();
}

void FaceRecognition::getFaceRecognitionCtrl(Ptr<FaceRecognitionCtrl> &_faceRecognitionCtrlPtr)
{
    _faceRecognitionCtrlPtr = faceRecognitionCtrlPtr;
}
