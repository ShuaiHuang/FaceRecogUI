#include "cascadedetector.h"

CascadeDetector::CascadeDetector(const string _cascadeFilePath)
    : faceCascadeFile(_cascadeFilePath)
{
    faceCascadeClassifier.load(faceCascadeFile);
}

CascadeDetector::~CascadeDetector()
{

}

void CascadeDetector::runDetection(Mat &_inputImg, vector<Rect> &_faceRects)
{
    _inputImg.copyTo(srcImg);
    if (faceCascadeClassifier.load(faceCascadeFile))
    {
        Mat grayImg;
        if (_inputImg.channels() == 3)
        {
            cvtColor(srcImg, grayImg, CV_BGR2GRAY);
        }
        else if (_inputImg.channels() == 1)
        {
            grayImg = _inputImg;
        }
        else
        {
            return;
        }

        equalizeHist(grayImg, grayImg);
        faceCascadeClassifier.detectMultiScale(
            grayImg,
            faceRects,
            1.1,
            2,
            0 | CASCADE_SCALE_IMAGE,
            Size(30, 30));
    }
    _faceRects = faceRects;
}
