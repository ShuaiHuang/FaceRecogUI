#include "FaceRecognitionView.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FaceRecognition w;
    w.show();

    return a.exec();
}
