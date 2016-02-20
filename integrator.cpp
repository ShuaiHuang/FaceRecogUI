#include "integrator.h"

Integrator::Integrator(Ptr<Tracker> _tracker)
{
    tracker = _tracker;
}


Integrator::~Integrator()
{
}

void Integrator::runIntegration(const Mat &_inputImg,
    vector<Rect> _detectedFaces,
    Rect2d _trackedFaces,
    Rect &_outputRect)
{
    Rect trackedFaces = cvtRect2d2Rect(_trackedFaces);
    int detectedFacesNum = _detectedFaces.size();
    int curFaceInd = 0;
    for (; curFaceInd < detectedFacesNum; curFaceInd++)
    {
        if (isRectsOverlap(_detectedFaces[curFaceInd], trackedFaces))
        {
            break;
        }
    }
    if (curFaceInd != detectedFacesNum)
    {
        _outputRect = _detectedFaces[curFaceInd];
    }
    else
    {
        _outputRect.x = 0;
        _outputRect.y = 0;
        _outputRect.height = 0;
        _outputRect.width = 0;
    }
}

template<class RectTemp>
bool Integrator::isRectsOverlap(RectTemp _rect1, RectTemp _rect2)
{
    int verDistance = abs(_rect1.y - _rect2.y);
    int horDistance = abs(_rect1.x - _rect2.x);

    int verThres = (_rect1.height + _rect2.height) / 2;
    int horThres = (_rect2.width + _rect2.width) / 2;

    if (verDistance > verThres || horDistance > horThres)
    {
        return false;
    }
    else
    {
        return true;
    }
}

Rect Integrator::cvtRect2d2Rect(Rect2d _inputRect)
{
    Rect outputRect;
    outputRect.x = _inputRect.x;
    outputRect.y = _inputRect.y;
    outputRect.width = _inputRect.width;
    outputRect.height = _inputRect.height;
    return outputRect;
}
