#include "facerecognitionmodel.h"

FaceRecognitionModel::FaceRecognitionModel(
        const int _faceDetectorInd,
        const int _faceTrackerInd,
        const int _faceRecognizerInd
        )
{
    setFaceDetector(_faceDetectorInd);
    setFaceTracker(_faceTrackerInd);
    setFaceRecognizer(_faceRecognizerInd);
}

void FaceRecognitionModel::setFaceDetector(int _faceDetectorInd)
{

}

void FaceRecognitionModel::setFaceTracker(int _faceTrackerInd)
{
    string trackerModelName;
    switch (_faceTrackerInd)
    {
    case TRACKER_TLD:
        trackerModelName = "TLD";
        break;
    case TRACKER_MIL:
        trackerModelName = "MIL";
        break;
    case TRACKER_BOOSTING:
        trackerModelName = "BOOSTING";
        break;
    case TRACKER_MEDIANFLOW:
        trackerModelName = "MEDIANFLOW";
        break;
    default:
        trackerModelName = "TLD";
        break;
    }
    faceTrackerPtr = Tracker::create(trackerModelName);
}

void FaceRecognitionModel::setFaceRecognizer(int _faceRecognizerInd)
{
    switch (_faceRecognizerInd)
    {
    case RECOGNIZER_EIGEN:
        faceRecognizerPtr = createEigenFaceRecognizer();
        break;
    case RECOGNIZER_FISHER:
        faceRecognizerPtr = createFisherFaceRecognizer();
        break;
    case RECOGNIZER_LBPH:
        faceRecognizerPtr = createLBPHFaceRecognizer();
        break;
    default:
        break;
    }
}

void FaceRecognitionModel::getFaceRecognizer(Ptr<FaceRecognizer> _faceRecognizerPtr)
{
    _faceRecognizerPtr = faceRecognizerPtr;
}

void FaceRecognitionModel::runFaceRecognition()
{

}
