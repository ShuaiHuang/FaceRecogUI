#include "systemctrl.h"

SystemCtrl::SystemCtrl()
{

}

void SystemCtrl::cvtMat2QImage(const Mat &_inputImg, QImage &_outputImg)
{
    if (!_inputImg.empty() && _inputImg.channels() == 3)
    {
        cvtColor(_inputImg, _inputImg, CV_BGR2RGB);
        _outputImg = QImage((const unsigned char *)_inputImg.data,
                            _inputImg.cols, _inputImg.rows, QImage::Format_RGB888);
        cvtColor(_inputImg, _inputImg, CV_RGB2BGR);
    }
    else
    {
        _outputImg = QImage((const unsigned char *)_inputImg.data,
                            _inputImg.cols, _inputImg.rows, QImage::Format_Grayscale8);
    }
}
