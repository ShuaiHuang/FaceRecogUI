#ifndef NPDDETECTOR_H
#define NPDDETECTOR_H

#include "facedetector.h"
#include "npdmodel.h"

struct CandicateFaceRect
{
    double row, col, size, score;
};

struct SelectedFaceRect
{
    int row, col, size, score, neighbors;
};

class NpdDetector : public FaceDetector
{
public:
    NpdDetector(string _modelFilePath);
    virtual ~NpdDetector();
    virtual void runDetection(Mat &_inputImg, vector<Rect> &_faceRects) override final;

private:
    Mat transposedImg;
    Ptr<NpdModel> npdModelPtr;
    vector<CandicateFaceRect> candicateFaceRects;
    vector<SelectedFaceRect> selectedFaceRects, finalRects;
    const float overlappingThreshold;

    void scanImg(Mat &_inputImg, int minFace = 40, int maxFace = 3000, int numThreads = 8);
    void mergeNearbyRects();
    void mergeEmbededRects();
    void checkBorders();

    void partition(InputArray &_inputArray, OutputArray &_label, int &_numGroups);
    int findRoot(int _node, InputArray &_parent);
    void logistic(vector<CandicateFaceRect> &_inputVec, InputArray _mask, OutputArray _outputVec);
};

#endif // NPDDETECTOR_H
