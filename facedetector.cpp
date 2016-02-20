#include "facedetector.h"

FaceDetector::FaceDetector()
{

}

FaceDetector::~FaceDetector()
{

}

void FaceDetector::visualizeFaceRects(Mat &_outputImg)
{
    srcImg.copyTo(_outputImg);
    const int rects = faceRects.size();
    if (rects)
    {
        for (int curInd = 0; curInd < rects; curInd++)
        {
            rectangle(_outputImg, faceRects[curInd], Scalar(0, 255, 0), 3);
            putText(
                        _outputImg,
                        to_string(curInd),
                        Point(faceRects[curInd].x, faceRects[curInd].y),
                        FONT_HERSHEY_SIMPLEX,
                        1.0,
                        Scalar(0, 255, 0),
                        3);
        }
    }
}
