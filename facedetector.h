#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <vector>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

class FaceDetector
{
public:
    FaceDetector();
    virtual ~FaceDetector();
    virtual void runDetection(Mat &_inputImg, vector<Rect> &_faceRects) = 0;

protected:
    Mat srcImg, dstImg;
    vector<Rect> faceRects;
};

#endif // FACEDETECTOR_H
