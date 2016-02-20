#ifndef CASCADEDETECTOR_H
#define CASCADEDETECTOR_H

#include "facedetector.h"
#include <opencv2/objdetect.hpp>

class CascadeDetector : public FaceDetector
{
public:
    CascadeDetector(const string _cascadeFilePath);
    virtual ~CascadeDetector();
    virtual void runDetection(Mat &_inputImg, vector<Rect> &_faceRects) override final;

private:
    const string faceCascadeFile;
    CascadeClassifier faceCascadeClassifier;
};

#endif // CASCADEDETECTOR_H
