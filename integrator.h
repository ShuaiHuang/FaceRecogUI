#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <vector>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
using namespace cv;

class Integrator
{
public:
    Integrator(Ptr<Tracker> _tracker);
    virtual ~Integrator();
    void runIntegration(
        const Mat &_inputImg,
        vector<Rect> _detectedFaces,
        Rect2d _trackedFaces,
        Rect &_outputRect
        );

private:
    Mat srcImg, dstImg;
    Ptr<Tracker> tracker;

    template<class RectTemp>
    bool isRectsOverlap(RectTemp _rect1, RectTemp _rect2);

    Rect cvtRect2d2Rect(Rect2d _inputRect);
};

#endif // INTEGRATOR_H
