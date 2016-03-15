#include "npddetector.h"

NpdDetector::NpdDetector(string _modelFilePath)
    : overlappingThreshold(0.5)
{
    npdModelPtr = makePtr<NpdModel>(_modelFilePath);
}

NpdDetector::~NpdDetector()
{
}

void NpdDetector::scanImg(
    Mat &_inputImg,
    int minFace,
    int maxFace,
    int numThreads)
{
    //TODO: Set openMP threads number here

    if (_inputImg.channels() != 1)
    {
        return;
    }

    minFace = max(minFace, npdModelPtr->getObjSize());
    maxFace = min(maxFace, min(srcImg.rows, srcImg.cols));

    if (min(srcImg.rows, srcImg.cols) < minFace)
    {
        return;
    }

    Mat_<int> winSize;
    npdModelPtr->getWinSize(winSize);
    for (int curScale = 0; curScale < npdModelPtr->numScales; curScale++)
    {
        if (winSize[0][curScale] < minFace)
        {
            continue;
        }
        else if (winSize[0][curScale] > maxFace)
        {
            break;
        }

        int winStep = int(floor(winSize[0][curScale] * 0.1));
        if (winSize[0][curScale] > 40)
        {
            winStep = int(floor(winSize[0][curScale] * 0.05));
        }

        vector<int> offsetTable(winSize[0][curScale] * winSize[0][curScale]);
        int tempPoint1 = 0, tempPoint2 = 0, gap = srcImg.rows - winSize[0][curScale];
        for (int curCol = 0; curCol < winSize[0][curScale]; curCol++)
        {
            for (int curRow = 0; curRow < winSize[0][curScale]; curRow++)
            {
                offsetTable[tempPoint1++] = tempPoint2++;
            }
            tempPoint2 += gap;
        }

        int colMax = srcImg.cols - winSize[0][curScale] + 1;
        int rowMax = srcImg.rows - winSize[0][curScale] + 1;

        // TODO: parallelize the for loop
        for (int curCol = 0; curCol < colMax; curCol += winStep)
        {
            const uchar *pixelPtr = transposedImg.data + curCol * srcImg.rows;
            for (int curRow = 0; curRow < rowMax; curRow += winStep, pixelPtr += winStep)
            {
                int treeIndex = 0;
                float _score = 0;
                int curStage;
                for (curStage = 0; curStage < npdModelPtr->numStages; curStage++)
                {
                    int node = npdModelPtr->treeRoot[treeIndex][0];

                    while (node > -1)
                    {
                        uchar p1 = pixelPtr[offsetTable[npdModelPtr->pixel1[node][curScale]]];
                        uchar p2 = pixelPtr[offsetTable[npdModelPtr->pixel2[node][curScale]]];
                        uchar fea = npdModelPtr->npdTable[p2][p1];
                        if (fea < npdModelPtr->cutpoint[node][0] || fea > npdModelPtr->cutpoint[node][1])
                        {
                            node = npdModelPtr->leftChild[node][0];
                        }
                        else
                        {
                            node = npdModelPtr->rightChild[node][0];
                        }
                    }

                    node = -node - 1;
                    _score = _score + npdModelPtr->fit[node][0];
                    treeIndex++;

                    if (_score < npdModelPtr->stageThreshold[curStage][0])
                    {
                        break;
                    }
                }

                if (curStage == npdModelPtr->numStages)
                {
                    CandicateFaceRect tempRect;
                    tempRect.row = curRow + 1;
                    tempRect.col = curCol + 1;
                    tempRect.size = npdModelPtr->winSize[0][curScale];
                    tempRect.score = _score;

                    // TODO: In SINGLE thread
                    candicateFaceRects.push_back(tempRect);
                }
            }
        }
    }
}

void NpdDetector::mergeNearbyRects()
{
    if (candicateFaceRects.empty())
    {
        return;
    }

    int numCandicates = candicateFaceRects.size();
    Mat_<int> predicate = Mat::eye(numCandicates, numCandicates, CV_8UC1);

    for (int curCanInd1 = 0; curCanInd1 < numCandicates; curCanInd1++)
    {
        for (int curCanInd2 = curCanInd1 + 1; curCanInd2 < numCandicates; curCanInd2++)
        {
            double h = min(
                candicateFaceRects[curCanInd1].row + candicateFaceRects[curCanInd1].size,
                candicateFaceRects[curCanInd2].row + candicateFaceRects[curCanInd2].size)
                - max(candicateFaceRects[curCanInd1].row,
                candicateFaceRects[curCanInd2].row);
            double w = min(
                candicateFaceRects[curCanInd1].col + candicateFaceRects[curCanInd1].size,
                candicateFaceRects[curCanInd2].col + candicateFaceRects[curCanInd2].size)
                - max(candicateFaceRects[curCanInd1].col,
                candicateFaceRects[curCanInd2].col);
            double s = max(h, 0.0) * max(w, 0.0);

            if (s / (pow(candicateFaceRects[curCanInd1].size, 2) + pow(candicateFaceRects[curCanInd2].size, 2) - s) > overlappingThreshold)
            {
                predicate[curCanInd1][curCanInd2] = 1;
                predicate[curCanInd2][curCanInd1] = 1;
            }
        }
    }

    Mat_<int> label;
    int numGroups = 0;
    partition(predicate, label, numGroups);

    for (int curCandiInd = 0; curCandiInd < numCandicates; curCandiInd++)
    {
        Mat1b mask = label == curCandiInd;
        if (sum(mask)[0] == 0)
        {
            continue;
        }
        Mat1d weight;
        logistic(candicateFaceRects, mask, weight);
        SelectedFaceRect tempSelRect;
        tempSelRect.score = sum(weight)[0];
        tempSelRect.neighbors = countNonZero(mask);

        if (tempSelRect.score == 0)
        {
            weight = Mat1d::ones(weight.size()) / weight.cols;
        }
        else
        {
            weight = weight / sum(weight)[0];
        }

        Mat1d tempSize;
        for (int curInd = 0; curInd < mask.cols; curInd++)
        {
            if (mask[0][curInd] != 0)
            {
                tempSize.push_back(candicateFaceRects[curInd].size);
            }
        }
        tempSelRect.size = floor(weight.dot(tempSize));

        Mat1d tempCol;
        for (int curInd = 0; curInd < mask.cols; curInd++)
        {
            if (mask[0][curInd] != 0)
            {
                tempCol.push_back(candicateFaceRects[curInd].col + candicateFaceRects[curInd].size / 2);
            }
        }
        tempSelRect.col = floor(weight.dot(tempCol) - tempSelRect.size / 2);

        Mat1d tempRow;
        for (int curInd = 0; curInd < mask.cols; curInd++)
        {
            if (mask[0][curInd] != 0)
            {
                tempRow.push_back(candicateFaceRects[curInd].row + candicateFaceRects[curInd].size / 2);
            }
        }
        tempSelRect.row = floor(weight.dot(tempRow) - tempSelRect.size / 2);

        selectedFaceRects.push_back(tempSelRect);
    }
}

void NpdDetector::mergeEmbededRects()
{
    if (candicateFaceRects.empty())
    {
        return;
    }

    const int candicatesNum = selectedFaceRects.size();
    Mat1b predicate = Mat::zeros(candicatesNum, candicatesNum, CV_16UC1);

    for (int curInd1 = 0; curInd1 < candicatesNum; curInd1++)
    {
        for (int curInd2 = curInd1 + 1; curInd2 < candicatesNum; curInd2++)
        {
            int h = min(selectedFaceRects[curInd1].row + selectedFaceRects[curInd1].size,
                selectedFaceRects[curInd2].row + selectedFaceRects[curInd2].size)
                - max(selectedFaceRects[curInd1].row, selectedFaceRects[curInd2].row);
            int w = min(selectedFaceRects[curInd1].col + selectedFaceRects[curInd1].size,
                selectedFaceRects[curInd2].col + selectedFaceRects[curInd2].size)
                - max(selectedFaceRects[curInd1].col, selectedFaceRects[curInd2].col);
            int s = max(h, 0) * max(w, 0);

            if (s / pow(selectedFaceRects[curInd1].size, 2) >= overlappingThreshold
                || s / pow(selectedFaceRects[curInd2].size, 2) >= overlappingThreshold)
            {
                predicate[curInd1][curInd2] = 1;
                predicate[curInd2][curInd1] = 1;
            }
        }
    }

    Mat1i flag = Mat::ones(1, candicatesNum, CV_16UC1);

    for (int curInd = 0; curInd < candicatesNum; curInd++)
    {
        vector<Point> location;
        findNonZero(predicate.col(curInd), location);

        if (location.empty())
        {
            continue;
        }

        int s = 0;
        for (int ind = 0; ind < location.size(); ind++)
        {
            s = max(s, selectedFaceRects[location[ind].y].score);
        }
        if (s > selectedFaceRects[curInd].score)
        {
            flag[0][curInd] = 0;
        }
    }

    for (int curInd = 0; curInd < candicatesNum; curInd++)
    {
        if (flag[0][curInd] == 1)
        {
            finalRects.push_back(selectedFaceRects[curInd]);
        }
    }
}

void NpdDetector::partition(InputArray &_inputArray, OutputArray &_label, int &_numGroups)
{
    Mat1i inputArray = _inputArray.getMat();

    int N = inputArray.rows;
    vector<int> parentVec(N, 0);
    for (int curInd = 0; curInd < N; curInd++)
    {
        parentVec[curInd] = curInd;
    }
    vector<int> rankVec(N, 0);

    for (int curRow = 0; curRow < N; curRow++)
    {
        for (int curCol = 0; curCol < N; curCol++)
        {
            if (inputArray[curRow][curCol] == 0)
            {
                continue;
            }

            int root1 = findRoot(curRow, parentVec);
            int root2 = findRoot(curCol, parentVec);

            if (root1 != root2)
            {
                if (rankVec[root2] < rankVec[root1])
                {
                    parentVec[root2] = root1;
                }
                else if (rankVec[root2] > rankVec[root1])
                {
                    parentVec[root1] = root2;
                }
                else
                {
                    parentVec[root2] = root1;
                    rankVec[root1] += 1;
                }
            }
        }
    }

    vector<bool> flag(N, false);
    _numGroups = 0;
    Mat_<int> label(1, N);
    int curGroup = 0;
    for (int curInd = 0; curInd < N; curInd++)
    {
        if (parentVec[curInd] == curInd)
        {
            flag[curInd] = true;
            _numGroups++;
            label[0][curInd] = curGroup++;
        }
    }

    for (int curInd = 0; curInd < N; curInd++)
    {
        if (parentVec[curInd] != curInd)
        {
            int root1 = findRoot(curInd, parentVec);
            label[0][curInd] = label[0][root1];
        }
    }

    label.copyTo(_label);
}

int NpdDetector::findRoot(int _node, InputArray &_parent)
{
    Mat_<int> parent = _parent.getMat();
    int root = parent[0][_node];
    if (root != _node)
    {
        root = findRoot(root, parent);
    }
    return root;
}

void NpdDetector::logistic(vector<CandicateFaceRect> &_inputVec, InputArray _mask, OutputArray _outputVec)
{
    if (_inputVec.empty() || _mask.empty())
    {
        return;
    }

    Mat1d outputVec;
    Mat1i mask = _mask.getMat();
    for (int curInd = 0; curInd < mask.cols; curInd++)
    {
        if (mask[0][curInd] != 0)
        {
            outputVec.push_back(_inputVec[curInd].score);
        }
    }

    exp(outputVec, outputVec);
    for (int curInd = 0; curInd < outputVec.cols; curInd++)
    {
        outputVec[0][curInd]++;
    }
    log(outputVec, outputVec);
    outputVec.copyTo(_outputVec);
}

void NpdDetector::checkBorders()
{
    int srcImgHeight = srcImg.rows;
    int srcImgWidth = srcImg.cols;
    int faceNum = finalRects.size();

    for (int curInd = 0; curInd < faceNum; curInd++)
    {
        Rect curFaceRect;
        curFaceRect.y = max(finalRects[curInd].row, 0);
        curFaceRect.x = max(finalRects[curInd].col, 0);

        curFaceRect.height = finalRects[curInd].size;
        curFaceRect.width = finalRects[curInd].size;

        if (curFaceRect.y + curFaceRect.height - 1 > srcImgHeight)
        {
            curFaceRect.height = srcImgHeight - curFaceRect.y + 1;
        }

        if (curFaceRect.x + curFaceRect.width - 1 > srcImgWidth)
        {
            curFaceRect.width = srcImgWidth - curFaceRect.x + 1;
        }

        faceRects.push_back(curFaceRect);
    }
}

void NpdDetector::runDetection(Mat &_inputImg, vector<Rect> &_faceRects)
{
    candicateFaceRects.clear();
    selectedFaceRects.clear();
    finalRects.clear();
    faceRects.clear();
    _faceRects.clear();

    _inputImg.copyTo(srcImg);
    srcImg.copyTo(dstImg);
    if (srcImg.channels() == 3)
    {
        cvtColor(dstImg, dstImg, CV_BGR2GRAY);
    }
    transpose(dstImg, transposedImg);

    scanImg(dstImg);
    mergeNearbyRects();
    mergeEmbededRects();
    checkBorders();

    _faceRects = faceRects;
}

