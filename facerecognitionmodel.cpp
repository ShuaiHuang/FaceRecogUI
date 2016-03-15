#include "facerecognitionmodel.h"

FaceRecognitionModel::FaceRecognitionModel(
        const int _faceDetectorInd,
        const int _faceTrackerInd,
        const int _faceRecognizerInd
        )
    : frontalDetectorModelFile(".\\data\\haarcascade_frontalface_default.xml")
{
    setFaceDetectorIndex(_faceDetectorInd);
    setFaceTrackerIndex(_faceTrackerInd);
    setFaceRecognizerIndex(_faceRecognizerInd);

    frontalFaceDetectorPtr = makePtr<CascadeDetector>(frontalDetectorModelFile);
    integratorPtr = makePtr<Integrator>(faceTrackerPtr);
}

void FaceRecognitionModel::setFaceDetectorIndex(int _faceDetectorInd)
{
    switch (_faceDetectorInd)
    {
    case DETECTOR_CASCADE:
        detectorModelFile = ".\\data\\haarcascade_frontalface_default.xml";
        faceDetectorPtr = makePtr<CascadeDetector>(detectorModelFile);
        break;
    case DETECTOR_NPD:
        detectorModelFile = ".\\data\\npdModel_frontal.xml";
        faceDetectorPtr = makePtr<NpdDetector>(detectorModelFile);
        break;
    default:
        detectorModelFile = ".\\data\\haarcascade_frontalface_default.xml";
        faceDetectorPtr = makePtr<CascadeDetector>(detectorModelFile);
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
        trackerModelName = "MIL";
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

void FaceRecognitionModel::runFaceRecognition(Mat &_dstImg, string &_faceInfo)
{
    vector<Rect> detectedFaceRectVec;
    Rect2d trackedFaceRect;

    faceDetectorPtr->runDetection(srcImg, detectedFaceRectVec);
    faceTrackerPtr->update(srcImg, trackedFaceRect);
    integratorPtr->runIntegration(srcImg, detectedFaceRectVec, trackedFaceRect, curIntegratedRect);
    if (curIntegratedRect.area())
    {
        recognizeFace(srcImg, curIntegratedRect, _faceInfo, faceRecognizerPtr, frontalFaceDetectorPtr);
        rectangle(dstImg, curIntegratedRect, Scalar(0, 0, 255), 5);
    }
    _dstImg = dstImg;
    prevIntegratedRect = curIntegratedRect;
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

void FaceRecognitionModel::recognizeFace(Mat &_srcFrame,
    Rect _faceRect,
    string &_outputName,
    Ptr<FaceRecognizer> &_faceRecognizer,
    Ptr<FaceDetector> &_faceDetector)
{
    Rect largeFaceRect = enlargeFaceRect(_srcFrame, _faceRect);
    Mat facePatch = _srcFrame(largeFaceRect);
    vector<Rect> faceRects;
    _faceDetector->runDetection(facePatch, faceRects);
    if (!faceRects.empty())
    {
        const int faceNum = faceRects.size();
        int maxAreaInd = 0, maxArea = faceRects[0].area();
        for (int curInd = 1; curInd < faceNum; curInd++)
        {
            int curArea = faceRects[curInd].area();
            if (curArea > maxArea)
            {
                maxAreaInd = curInd;
                maxArea = curArea;
            }
        }
        Mat frontalFace = facePatch(faceRects[maxAreaInd]);
        cvtColor(frontalFace, frontalFace, CV_BGR2GRAY);
        int label = _faceRecognizer->predict(frontalFace);
        _outputName = _faceRecognizer->getLabelInfo(label);
    }
}

Rect FaceRecognitionModel::enlargeFaceRect(Mat &_srcFrame, Rect _faceRect)
{
    Rect retFaceRect;
    retFaceRect.x = max(0.0, _faceRect.x - 0.5 * _faceRect.width);
    retFaceRect.y = max(0.0, _faceRect.y - 0.5 * _faceRect.height);
    retFaceRect.height = min(double(_srcFrame.rows - retFaceRect.x), 2.0 * _faceRect.height);
    retFaceRect.width = min(double(_srcFrame.cols - retFaceRect.y), 2.0 * _faceRect.width);
    return retFaceRect;
}
