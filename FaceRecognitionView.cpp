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
    ui->selectionButton->setEnabled(false);
    ui->playButton->setEnabled(false);
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
    QMessageBox::about(this, "About", "by Shuai Huang, PAMI Lab\n shuaihuang@sjtu.edu.cn\n All copyright reserved.");
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
        emit ui->nextFrameButton->clicked();

        ui->nextFrameButton->setEnabled(true);
        ui->recogResultTxtBrowser->append("Video loaded.");
    }
}

void FaceRecognition::on_nextFrameButton_clicked()
{
    if (faceRecognitionCtrlPtr->getVideoCaptureNextFrame())
    {
        QImage dstImg;
        int facesNum;
        faceRecognitionCtrlPtr->runFaceDetection(dstImg, facesNum);

        dstImg = dstImg.scaled(340, 260, Qt::KeepAspectRatio);
        ui->videoDisplayLabel->setPixmap(QPixmap::fromImage(dstImg));

        ui->faceIndComboBox->setEnabled(false);
        ui->faceIndComboBox->clear();
        ui->selectionButton->setEnabled(false);
        if (facesNum > 0)
        {
            ui->selectionButton->setEnabled(true);
            ui->faceIndComboBox->setEnabled(true);
            for (int curFaceInd = 0; curFaceInd < facesNum; curFaceInd++)
            {
                ui->faceIndComboBox->addItem(QString::number(curFaceInd));
            }
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Video finished.", QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void FaceRecognition::on_selectionButton_clicked()
{
    int selectedFaceInd = ui->faceIndComboBox->currentIndex();
    if (faceRecognitionCtrlPtr->initializeTracker(selectedFaceInd))
    {
        ui->playButton->setEnabled(true);
        ui->faceIndComboBox->setEnabled(false);
        ui->nextFrameButton->setEnabled(false);
        ui->selectionButton->setEnabled(false);
        ui->recogResultTxtBrowser->append("Face selected.");
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Face index error.", QMessageBox::Ok, QMessageBox::NoButton);
    }
}

void FaceRecognition::on_playButton_clicked()
{
    QImage dstImg;
    QString faceInfo;

    ui->recogResultTxtBrowser->append("Start to recognize.");
    ui->playButton->setEnabled(false);
    while (faceRecognitionCtrlPtr->getVideoCaptureNextFrame())
    {
        faceRecognitionCtrlPtr->runFaceRecognition(dstImg, faceInfo);
        dstImg = dstImg.scaled(340, 260, Qt::KeepAspectRatio);
        QCoreApplication::processEvents();
        ui->videoDisplayLabel->clear();
        ui->videoDisplayLabel->setPixmap(QPixmap::fromImage(dstImg));
        if (!faceInfo.isEmpty())
        {
            ui->recogResultTxtBrowser->append(faceInfo);
        }
    }
}
