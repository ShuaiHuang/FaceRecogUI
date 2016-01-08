#include "facerecognition.h"
#include "ui_facerecognition.h"
#include "faceregistration.h"

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
