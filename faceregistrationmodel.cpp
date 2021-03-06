#include "faceregistrationmodel.h"

FaceRegistrationModel::FaceRegistrationModel(Ptr<FaceRecognizer> _faceRecognizerPtr)
    : classifierFileName(".\\data\\haarcascade_frontalface_default.xml"),
      faceRecognizerFileName(".\\data\\face_recognizer.xml"),
      faceRecognizerPtr(_faceRecognizerPtr)
{
    faceDetectorPtr = makePtr<CascadeDetector>(classifierFileName);
}

void FaceRegistrationModel::updateFaceRecognizer(vector<Mat> &_faceImgVec,
        vector<int> &_faceLabelVec,
        vector<string> _faceInfoVec)
{
    faceRecognizerPtr->train(_faceImgVec, _faceLabelVec);
    int faceRegNum = _faceImgVec.size();
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
        faceDetectorPtr->runDetection(srcImg, faceRects);
        _outputRects = faceRects;
    }
}
