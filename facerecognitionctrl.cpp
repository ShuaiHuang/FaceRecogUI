#include "facerecognitionctrl.h"

FaceRecognitionCtrl::FaceRecognitionCtrl()
    : optionsFileName(":/data/optionsData")
{
    faceRecognitionModelPtr = make_shared<FaceRecognitionModel>();
    loadOptions();
}

void FaceRecognitionCtrl::runFaceRecognization()
{
    faceRecognitionModelPtr->runFaceRecognition();
}

void FaceRecognitionCtrl::getFaceRecognizer(Ptr<FaceRecognizer> &_faceRecognizer)
{
    faceRecognitionModelPtr->getFaceRecognizer(_faceRecognizer);
}

void FaceRecognitionCtrl::setFaceDetector(int _faceDetectorInd)
{
    faceRecognitionModelPtr->setFaceDetectorIndex(_faceDetectorInd);
}

void FaceRecognitionCtrl::setFaceTracker(int _faceTrackerInd)
{
    faceRecognitionModelPtr->setFaceTrackerIndex(_faceTrackerInd);
}

void FaceRecognitionCtrl::setFaceRecognizer(int _faceRecognizerInd)
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
        setFaceDetector(faceDetectorInd);
        setFaceTracker(faceTrackerInd);
        setFaceRecognizer(faceRecognizerInd);
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
