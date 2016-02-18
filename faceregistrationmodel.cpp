#include "faceregistrationmodel.h"

FaceRegistrationModel::FaceRegistrationModel(Ptr<FaceRecognizer> _faceRecognizerPtr)
    : classifierFileName(".\\data\\haarcascade_frontalface_default.xml"),
      faceRecognizerFileName(".\\data\\face_recognizer.xml"),
      faceRecognizerPtr(_faceRecognizerPtr)
{
    cascadeClassifier.load(classifierFileName);
}

void FaceRegistrationModel::updateFaceRecognizer(
        int _faceInd,
        int _faceLabel,
        string _faceInfo)
{
    vector<Mat> faces = {srcImg(faceRects[_faceInd])};
    vector<int> labels = {_faceLabel};
    faceRecognizerPtr->update(faces, labels);
    if (!_faceInfo.empty())
    {
        faceRecognizerPtr->setLabelInfo(_faceLabel, _faceInfo);
    }
}

void FaceRegistrationModel::saveFaceRecognizer()
{
    faceRecognizerPtr->save(faceRecognizerFileName);
}

void FaceRegistrationModel::detectFaces(const Mat &_inputImg, vector<Rect> &_outputRects)
{
    if (!_inputImg.empty())
    {
        _inputImg.copyTo(srcImg);
        cvtColor(srcImg, srcImg, CV_BGR2GRAY);
        cascadeClassifier.detectMultiScale(srcImg, faceRects, 1.2, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
        _outputRects = faceRects;
    }
}
