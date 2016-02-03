#include "faceregistrationmodel.h"

FaceRegistrationModel::FaceRegistrationModel(Ptr<FaceRecognizer> _faceRecognizerPtr, string _faceRecognizerFileName)
    : classifierFileName(":/data/cascadeClassifier"),
      faceRecognizerFileName(_faceRecognizerFileName),
      faceRecognizerPtr(_faceRecognizerPtr)
{
    cascadeClassifier.load(classifierFileName);
}

void FaceRegistrationModel::updateFaceRecognizer(
        int _faceInd,
        int _faceLabel,
        string _faceInfo)
{
    faceRecognizerPtr->update(srcImg(faceRects[_faceInd]), _label);
    faceRecognizerPtr->setLabelInfo(_label, _faceInfo);
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
        cascadeClassifier.detectMultiScale(srcImg, faceRects, 1.2, 3, 0, Size(40, 40));
        _outputRects = faceRects;
    }
}
