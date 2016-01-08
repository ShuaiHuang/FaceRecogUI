#include "faceregistration.h"
#include "ui_faceregistration.h"

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
