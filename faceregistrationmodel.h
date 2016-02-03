#ifndef FACEREGISTRATIONMODEL_H
#define FACEREGISTRATIONMODEL_H

#include <string>
#include <vector>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/face.hpp>
using namespace cv;
using namespace face;

class FaceRegistrationModel
{
public:
    FaceRegistrationModel(Ptr<FaceRecognizer> _faceRecognizer, string _faceRecognizerFileName);
    void updateFaceRecognizer(int _faceInd, int _faceLabel, string _faceInfo);
    void saveFaceRecognizer();
    void detectFaces(const Mat &_inputImg, vector<Rect> &_outputRects);

private:
    CascadeClassifier cascadeClassifier;
    Ptr<FaceRecognizer> faceRecognizerPtr;
    string classifierFileName;
    string faceRecognizerFileName;
    int facesNumber;
    Mat srcImg;
    vector<Rect> faceRects;
};

#endif // FACEREGISTRATIONMODEL_H
