#include "NpdModel.h"

NpdModel::NpdModel(string _filePath)
{
    loadData(_filePath);
}

NpdModel::~NpdModel()
{
}

void NpdModel::loadData(string _filePath)
{
    FileStorage fileStorage(_filePath, FileStorage::READ);
    fileStorage["objSize"] >> objSize;
    fileStorage["numStages"] >> numStages;
    fileStorage["numBranchNodes"] >> numBranchNodes;
    fileStorage["numLeafNodes"] >> numLeafNodes;
    fileStorage["numScales"] >> numScales;
    fileStorage["scaleFactor"] >> scaleFactor;
    fileStorage["stageThreshold"] >> stageThreshold;
    fileStorage["fit"] >> fit;
    fileStorage["treeRoot"] >> treeRoot;
    fileStorage["pixel1"] >> pixel1;
    fileStorage["pixel2"] >> pixel2;
    fileStorage["cutpoint"] >> cutpoint;
    fileStorage["leftChild"] >> leftChild;
    fileStorage["rightChild"] >> rightChild;
    fileStorage["npdTable"] >> npdTable;
    fileStorage["winSize"] >> winSize;
    fileStorage.release();
}

int NpdModel::getObjSize()
{
    return objSize;
}

int NpdModel::getNumStages()
{
    return numStages;
}

int NpdModel::getNumBranchNodes()
{
    return numBranchNodes;
}

int NpdModel::getNumLeafNodes()
{
    return numLeafNodes;
}

int NpdModel::getNumScales()
{
    return numScales;
}

float NpdModel::getScaleFactor()
{
    return scaleFactor;
}

void NpdModel::getStageThreshold(Mat_<float> &_stageThreshold)
{
    _stageThreshold = stageThreshold;
}

void NpdModel::getFit(Mat_<float> &_fit)
{
    _fit = fit;
}

void NpdModel::getTreeRoot(Mat_<int> &_treeRoot)
{
    _treeRoot = treeRoot;
}

void NpdModel::getPixel1(Mat_<int> &_pixel1)
{
    _pixel1 = pixel1;
}

void NpdModel::getPixel2(Mat_<int> &_pixel2)
{
    _pixel2 = pixel2;
}

void NpdModel::getCutpoint(Mat_<int> &_cutpoint)
{
    _cutpoint = cutpoint;
}

void NpdModel::getLeftChild(Mat_<int> &_leftChild)
{
    _leftChild = leftChild;
}

void NpdModel::getRightChild(Mat_<int> &_rightChild)
{
    _rightChild = rightChild;
}

void NpdModel::getNpdTable(Mat_<int> &_npdTable)
{
    _npdTable = npdTable;
}

void NpdModel::getWinSize(Mat_<int> &_winSize)
{
    _winSize = winSize;
}

