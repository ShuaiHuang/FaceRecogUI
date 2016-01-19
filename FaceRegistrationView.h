#ifndef FACEREGISTRATIONVIEW_H
#define FACEREGISTRATIONVIEW_H

#include <QDialog>

namespace Ui {
class FaceRegistration;
}

class FaceRegistration : public QDialog
{
    Q_OBJECT

public:
    explicit FaceRegistration(QWidget *parent = 0);
    ~FaceRegistration();

private:
    Ui::FaceRegistration *ui;
};

#endif // FACEREGISTRATIONVIEW_H
