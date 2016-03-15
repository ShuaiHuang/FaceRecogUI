#ifndef NPDMODEL_H
#define NPDMODEL_H

#include <iostream>
using namespace std;

#include <opencv2/core.hpp>
using namespace cv;

class NpdModel
{
public:
    NpdModel(string _filePath);
    ~NpdModel();

        int getObjSize();
        int getNumStages();
        int getNumBranchNodes();
        int getNumLeafNodes();
        int getNumScales();
        float getScaleFactor();
        void getStageThreshold(Mat_<float> &_stageThreshold);
        void getFit(Mat_<float> &_fit);
        void getTreeRoot(Mat_<int> &_treeRoot);
        void getPixel1(Mat_<int> &_pixel1);
        void getPixel2(Mat_<int> &_pixel2);
        void getCutpoint(Mat_<int> &_cutpoint);
        void getLeftChild(Mat_<int> &_leftChild);
        void getRightChild(Mat_<int> &_rightChild);
        void getNpdTable(Mat_<int> &_npdTable);
        void getWinSize(Mat_<int> &_winSize);

        int objSize;
        int numStages;
        int numBranchNodes;
        int numLeafNodes;
        float scaleFactor;
        int numScales;
        Mat_<float> stageThreshold;
        Mat_<float> fit;
        Mat_<int> treeRoot;
        Mat_<int> pixel1;
        Mat_<int> pixel2;
        Mat_<int> cutpoint;
        Mat_<int> leftChild;
        Mat_<int> rightChild;
        Mat_<int> npdTable;
        Mat_<int> winSize;

    private:
        void loadData(string _filePath);
};

#endif // NPDMODEL_H
