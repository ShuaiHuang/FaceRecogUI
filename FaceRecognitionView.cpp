#include "FaceRecognitionView.h"
#include "ui_facerecognition.h"
#include "FaceRegistrationView.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <QMessageBox>

FaceRecognition::FaceRecognition(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FaceRecognition)
{
    ui->setupUi(this);
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
    QMessageBox::about(this, tr("About"), tr("Made by Shuai Huang, PAMI Lab"));
}

void FaceRecognition::on_actionRegister_Face_triggered()
{
    FaceRegistration faceReg(this);
    faceReg.exec();
}
