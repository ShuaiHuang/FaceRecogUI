#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T13:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceRecognitionSys
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    FaceRecognitionView.cpp \
    systemctrl.cpp \
    facerecognitionctrl.cpp \
    facerecognitionmodel.cpp \
    faceregistrationctrl.cpp \
    faceregistrationmodel.cpp \
    FaceRegistrationView.cpp \
    facedetector.cpp \
    cascadedetector.cpp \
    integrator.cpp

HEADERS  += \
    FaceRecognitionView.h \
    systemctrl.h \
    facerecognitionctrl.h \
    facerecognitionmodel.h \
    faceregistrationctrl.h \
    faceregistrationmodel.h \
    FaceRegistrationView.h \
    facedetector.h \
    cascadedetector.h \
    integrator.h

FORMS    += facerecognition.ui \
    faceregistration.ui

INCLUDEPATH += D:/Codes/opencv_build/install/include \
                D:/Codes/opencv_build/install/include/opencv \
                D:/Codes/opencv_build/install/include/opencv2

LIBS += D:/Codes/opencv_build/install/x64/vc12/lib/opencv_core300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_imgcodecs300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_imgproc300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_imgproc300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_videoio300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_objdetect300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_face300d.lib \
        D:/Codes/opencv_build/install/x64/vc12/lib/opencv_tracking300d.lib

#INCLUDEPATH += E:/opencv_build/install/include \
#                E:/opencv_build/install/include/opencv \
#                E:/opencv_build/install/include/opencv2

#LIBS += E:/opencv_build/install/x64/vc12/lib/opencv_core300d.lib \
#        E:/opencv_build/install/x64/vc12/lib/opencv_imgcodecs300d.lib \
#        E:/opencv_build/install/x64/vc12/lib/opencv_imgproc300d.lib

RESOURCES += \
    facerecognitionres.qrc
