#include "facerecognitionmodel.h"

FaceRecognitionModel::FaceRecognitionModel(
        const int _faceDetectorInd,
        const int _faceTrackerInd,
        const int _faceRecognizerInd
        )
    : cascadeDetectorFile(".\\data\\haarcascade_frontalface_default.xml")
{
    setFaceDetectorIndex(_faceDetectorInd);
    setFaceTrackerIndex(_faceTrackerInd);
    setFaceRecognizerIndex(_faceRecognizerInd);

    frontalFaceDetectorPtr = makePtr<CascadeDetector>(cascadeDetectorFile);
    integratorPtr = makePtr<Integrator>(faceTrackerPtr);
}

void FaceRecognitionModel::setFaceDetectorIndex(int _faceDetectorInd)
{
    switch (_faceDetectorInd)
    {
    case DETECTOR_CASCADE:
        faceDetectorPtr = makePtr<CascadeDetector>(cascadeDetectorFile);
        break;
    default:
        faceDetectorPtr = makePtr<CascadeDetector>(cascadeDetectorFile);
    }

}

void FaceRecognitionModel::setFaceTrackerIndex(int _faceTrackerInd)
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
    }
    faceTrackerPtr = Tracker::create(trackerModelName);
}

void FaceRecognitionModel::setFaceRecognizerIndex(int _faceRecognizerInd)
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
        faceRecognizerPtr = createLBPHFaceRecognizer();
    }
}

void FaceRecognitionModel::getFaceRecognizer(Ptr<FaceRecognizer> &_faceRecognizerPtr)
{
    _faceRecognizerPtr = faceRecognizerPtr;
}

void FaceRecognitionModel::runFaceRecognition()
{

}

void FaceRecognitionModel::loadVideo(string _videoFile)
{
    videoCapture.open(_videoFile);
}

bool FaceRecognitionModel::getVideoCaptureNextFrame()
{
    videoCapture >> srcImg;
    if (!srcImg.empty())
    {
        srcImg.copyTo(dstImg);
        return true;
    }
    else
    {
        return false;
    }
}

void FaceRecognitionModel::runFaceDetection(Mat &_dstImg, int &_facesNum)
{
    if (!dstImg.empty())
    {
        faceDetectorPtr->runDetection(srcImg, faceRectVec);
        faceDetectorPtr->visualizeFaceRects(dstImg);
        _dstImg = dstImg;
        _facesNum = faceRectVec.size();
    }
}

bool FaceRecognitionModel::initializeTracker(const int &_selectedFaceInd)
{
    if (_selectedFaceInd > faceRectVec.size())
    {
        return false;
    }
    else
    {
        return faceTrackerPtr->init(srcImg, faceRectVec[_selectedFaceInd]);
    }
}
