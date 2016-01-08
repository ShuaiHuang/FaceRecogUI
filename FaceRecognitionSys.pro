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
        facerecognition.cpp \
    faceregistration.cpp

HEADERS  += facerecognition.h \
    faceregistration.h

FORMS    += facerecognition.ui \
    faceregistration.ui
