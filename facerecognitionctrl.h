#ifndef FACERECOGNITIONCTRL_H
#define FACERECOGNITIONCTRL_H

#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QTextStream>

#include "systemctrl.h"
#include "facerecognitionmodel.h"

class FaceRecognitionCtrl : public SystemCtrl
{
public:
    FaceRecognitionCtrl();
    void runFaceRecognization();
    void getFaceRecognizer(Ptr<FaceRecognizer> _faceRecognizer = Ptr<FaceRecognizer>());
    void setFaceDetector(int _faceDetectorInd);
    void setFaceTracker(int _faceTrackerInd);
    void setFaceRecognizer(int _faceRecognizerInd);
    bool loadOptions();
    bool saveOptions(int _faceDetectorInd, int _faceTrackerInd, int _faceRecognizerInd);

private:
    QString optionsFileName;
    FaceRecognitionModel faceRecognitionModel;
};

#endif // FACERECOGNITIONCTRL_H
