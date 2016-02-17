#ifndef FACEREGISTRATIONCTRL_H
#define FACEREGISTRATIONCTRL_H

#include <string>
#include <vector>
using namespace std;

#include "systemctrl.h"
#include "faceregistrationmodel.h"
#include "facerecognitionctrl.h"

#include <QFileInfo>

#define IMAGE_FROM_FILE 0
#define IMAGE_FROM_VIDEO 1

class FaceRegistrationCtrl : public SystemCtrl
{
public:
    FaceRegistrationCtrl(Ptr<FaceRecognizer> &_faceRecognizer);

    void loadImage(int _imageSourceIndicator, QString _filePath);
    void detectFaces(QImage &_dstImg);
    void registerFace(int _faceInd, int _faceLabel, QString _faceInfo);
    void saveFaceRecognizer();

private:
    shared_ptr<FaceRegistrationModel> faceRegistrationModelPtr;
    Mat srcImg, dstImg;
    vector<Rect> faceRects;

    void drawFaceRects();
};

#endif // FACEREGISTRATIONCTRL_H
