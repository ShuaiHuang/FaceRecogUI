#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T13:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceRecognitionSys
TEMPLATE = app


SOURCES += main.cpp\
    FaceRegistrationView.cpp \
    FaceRecognitionView.cpp

HEADERS  += \
    FaceRegistrationView.h \
    FaceRecognitionView.h

FORMS    += facerecognition.ui \
    faceregistration.ui

INCLUDEPATH += D:/Codes/opencv_build/install/include \
                D:/Codes/opencv_build/install/include/opencv \
                D:/Codes/opencv_build/install/include/opencv2

LIBS += D:/Codes/opencv_build/install/x64/vc12/lib/opencv_core300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_imgcodecs300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_imgproc300d.lib
