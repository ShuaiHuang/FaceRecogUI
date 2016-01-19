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
