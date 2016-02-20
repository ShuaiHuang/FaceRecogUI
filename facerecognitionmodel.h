#ifndef FACERECOGNITIONMODEL_H
#define FACERECOGNITIONMODEL_H

#include <vector>
#include <string>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/face.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace face;

#include "facedetector.h"
#include "cascadedetector.h"

#define TRACKER_TLD 0
#define TRACKER_MIL 1
#define TRACKER_BOOSTING 2
#define TRACKER_MEDIANFLOW 3

#define RECOGNIZER_EIGEN 0
#define RECOGNIZER_FISHER 1
#define RECOGNIZER_LBPH 2

#define DETECTOR_LIBFACE 0
#define DETECTOR_NPD 1
#define DETECTOR_CASCADE 2

#define NOT_DEFINED -1

class FaceRecognitionModel
{
public:
    FaceRecognitionModel(
            const int _faceDetectorInd = NOT_DEFINED,
            const int _faceTrackerInd = NOT_DEFINED,
            const int _faceRecognizerInd = NOT_DEFINED);

    void getFaceRecognizer(Ptr<FaceRecognizer> &_faceRecognizerPtr);
    void runFaceRecognition();
    void setFaceTrackerIndex(int _faceTrackerInd);
    void setFaceRecognizerIndex(int _faceRecognizerInd);
    void setFaceDetectorIndex(int _faceDetectorInd);
    void loadVideo(string _videoFile);
    bool getVideoCaptureNextFrame();
    void runFaceDetection(Mat &_dstImg, int &_facesNum);

private:
    const string cascadeDetectorFile;
    Ptr<FaceDetector> faceDetectorPtr;
    Ptr<Tracker> faceTrackerPtr;
    Ptr<FaceRecognizer> faceRecognizerPtr;
    VideoCapture videoCapture;
    Mat srcImg, dstImg;
    vector<Rect> faceRectVec;
};

#endif // FACERECOGNITIONMODEL_H
