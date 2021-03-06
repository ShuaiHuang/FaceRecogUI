#include "facerecognitionctrl.h"

FaceRecognitionCtrl::FaceRecognitionCtrl()
    : optionsFileName(":/data/optionsData")
{
    faceRecognitionModelPtr = make_shared<FaceRecognitionModel>();
    loadOptions();
}

void FaceRecognitionCtrl::runFaceRecognition(QImage &_dstImg, QString &_faceInfo)
{
    Mat dstImg;
    string faceInfo;
    faceRecognitionModelPtr->runFaceRecognition(dstImg, faceInfo);
    cvtMat2QImage(dstImg, _dstImg);
    _faceInfo = QString::fromStdString(faceInfo);
}

void FaceRecognitionCtrl::getFaceRecognizer(Ptr<FaceRecognizer> &_faceRecognizer)
{
    faceRecognitionModelPtr->getFaceRecognizer(_faceRecognizer);
}

void FaceRecognitionCtrl::setFaceDetectorIndex(int _faceDetectorInd)
{
    faceRecognitionModelPtr->setFaceDetectorIndex(_faceDetectorInd);
}

void FaceRecognitionCtrl::setFaceTrackerIndex(int _faceTrackerInd)
{
    faceRecognitionModelPtr->setFaceTrackerIndex(_faceTrackerInd);
}

void FaceRecognitionCtrl::setFaceRecognizerIndex(int _faceRecognizerInd)
{
    faceRecognitionModelPtr->setFaceRecognizerIndex(_faceRecognizerInd);
}

bool FaceRecognitionCtrl::loadOptions()
{
    QFileInfo optionsFileInfo(optionsFileName);
    int faceDetectorInd, faceTrackerInd, faceRecognizerInd;
    if (optionsFileInfo.exists() && optionsFileInfo.isFile())
    {
        QFile optionsFile(optionsFileName);
        if (!optionsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }
        QTextStream textStream(&optionsFile);
        textStream >> faceDetectorInd >> faceTrackerInd >> faceRecognizerInd;
        setFaceDetectorIndex(faceDetectorInd);
        setFaceTrackerIndex(faceTrackerInd);
        setFaceRecognizerIndex(faceRecognizerInd);
        return true;
    }
    else
    {
        QFile optionsFile(optionsFileName);
        optionsFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream textStream(&optionsFile);
        textStream << QString::number(DETECTOR_NPD) << endl;
        textStream << QString::number(TRACKER_TLD) << endl;
        textStream << QString::number(RECOGNIZER_LBPH) << endl;
        optionsFile.close();
        return true;
    }
}

bool FaceRecognitionCtrl::saveOptions(int _faceDetectorInd, int _faceTrackerInd, int _faceRecognizerInd)
{
    QFile optionsFile(optionsFileName);
    if (!optionsFile.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QTextStream textStream(&optionsFile);
    textStream << _faceDetectorInd << endl;
    textStream << _faceTrackerInd << endl;
    textStream << _faceRecognizerInd << endl;
    optionsFile.close();
    return true;
}

void FaceRecognitionCtrl::loadVideo(QString _videoFile)
{
    faceRecognitionModelPtr->loadVideo(_videoFile.toStdString());
}

bool FaceRecognitionCtrl::getVideoCaptureNextFrame()
{
    return faceRecognitionModelPtr->getVideoCaptureNextFrame();
}

void FaceRecognitionCtrl::runFaceDetection(QImage &_dstImg, int &_facesNum)
{
    Mat dstImg;
    faceRecognitionModelPtr->runFaceDetection(dstImg, _facesNum);
    cvtMat2QImage(dstImg, _dstImg);
}

bool FaceRecognitionCtrl::initializeTracker(const int &_selectedFaceInd)
{
    return faceRecognitionModelPtr->initializeTracker(_selectedFaceInd);
}
