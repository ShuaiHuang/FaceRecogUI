#include "faceregistrationmodel.h"

FaceRegistrationModel::FaceRegistrationModel(Ptr<FaceRecognizer> _faceRecognizerPtr)
    : classifierFileName(".\\data\\haarcascade_frontalface_default.xml"),
      faceRecognizerFileName(".\\data\\face_recognizer.xml"),
      faceRecognizerPtr(_faceRecognizerPtr)
{
    cascadeClassifier.load(classifierFileName);
}

void FaceRegistrationModel::updateFaceRecognizer(vector<Mat> &_faceImgVec,
        vector<int> &_faceLabelVec,
        vector<string> _faceInfoVec)
{
    faceRecognizerPtr->train(_faceImgVec, _faceLabelVec);
    const int faceRegNum = _faceImgVec.size();
    for (int curFaceInd = 0; curFaceInd < faceRegNum; curFaceInd++)
    {
        if (_faceInfoVec[curFaceInd] != "")
        {
            faceRecognizerPtr->setLabelInfo(_faceLabelVec[curFaceInd], _faceInfoVec[curFaceInd]);
        }
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
