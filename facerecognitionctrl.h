#ifndef FACERECOGNITIONCTRL_H
#define FACERECOGNITIONCTRL_H

#include <memory>

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
    void getFaceRecognizer(Ptr<FaceRecognizer> &_faceRecognizer);
    void setFaceDetector(int _faceDetectorInd);
    void setFaceTracker(int _faceTrackerInd);
    void setFaceRecognizer(int _faceRecognizerInd);
    bool loadOptions();
    bool saveOptions(int _faceDetectorInd, int _faceTrackerInd, int _faceRecognizerInd);
    void loadVideo(QString _videoFile);

private:
    QString optionsFileName;
    shared_ptr<FaceRecognitionModel> faceRecognitionModelPtr;
};

#endif // FACERECOGNITIONCTRL_H
