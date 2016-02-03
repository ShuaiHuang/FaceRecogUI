#include "FaceRegistrationView.h"
#include "ui_faceregistration.h"

FaceRegistration::FaceRegistration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FaceRegistration)
{
    ui->setupUi(this);
    isCameraPaused = true;
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
    if (!checked)
    {
        isCameraPaused = true;
        ui->startPauseButton->setText("Start");
    }
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
