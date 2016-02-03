#ifndef SYSTEMCTRL_H
#define SYSTEMCTRL_H

#include <QImage>
#include <QString>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

class SystemCtrl
{
public:
    SystemCtrl();

    static void cvtMat2QImage(const Mat &_inputImg, QImage &_outputImg);
};

#endif // SYSTEMCTRL_H
