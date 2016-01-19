#include "FaceRegistrationView.h"
#include "ui_faceregistration.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

FaceRegistration::FaceRegistration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceRegistration)
{
    ui->setupUi(this);
}

FaceRegistration::~FaceRegistration()
{
    delete ui;
}

void FaceRegistration::on_loadImgButton_clicked()
{

}

void FaceRegistration::on_imgRadioButton_toggled(bool checked)
{
    ui->loadImgButton->setEnabled(checked);
}

void FaceRegistration::on_cameraRadioButton_toggled(bool checked)
{
    ui->startPauseButton->setEnabled(checked);
}
