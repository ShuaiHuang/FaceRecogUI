#include "faceregistrationctrl.h"

FaceRegistrationCtrl::FaceRegistrationCtrl(Ptr<FaceRecognizer> &_faceRecognizer)
{
    faceRegistrationModelPtr = make_shared<FaceRegistrationModel>(_faceRecognizer);
}

void FaceRegistrationCtrl::loadImage(int _imageSourceIndicator, QString _filePath)
{
    QFileInfo fileInfo(_filePath);
    if (!fileInfo.exists() || fileInfo.isDir())
    {
        return;
    }

    switch (_imageSourceIndicator)
    {
    case IMAGE_FROM_FILE:
        srcImg = imread(_filePath.toStdString());
        srcImg.copyTo(dstImg);
        break;
    case IMAGE_FROM_VIDEO:
        break;
    default:
        break;
    }
}

void FaceRegistrationCtrl::detectFaces(QImage &_dstImg)
{
    if (srcImg.empty())
    {
        return;
    }

    faceRegistrationModelPtr->detectFaces(srcImg, faceRects);
    drawFaceRects();
    cvtMat2QImage(dstImg, _dstImg);
}

void FaceRegistrationCtrl::registerFace(int _faceInd, int _faceLabel, QString _faceInfo)
{
    faceRegistrationModelPtr->updateFaceRecognizer(_faceInd, _faceLabel, _faceInfo.toStdString());
}

void FaceRegistrationCtrl::saveFaceRecognizer()
{
    faceRegistrationModelPtr->saveFaceRecognizer();
}

void FaceRegistrationCtrl::drawFaceRects()
{
    if (dstImg.empty() || faceRects.empty())
    {
        return;
    }

    const int rectsNum = faceRects.size();
    for (int curInd = 0; curInd < rectsNum; curInd++)
    {
        rectangle(dstImg, faceRects[curInd], Scalar(0, 255, 0), 3);
        putText(
                    dstImg,
                    to_string(curInd),
                    Point(faceRects[curInd].x, faceRects[curInd].y),
                    FONT_HERSHEY_SIMPLEX,
                    1.0,
                    Scalar(0, 255, 0),
                    3);
    }
}
