#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T02:38:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageMapper
TEMPLATE = app

SOURCES += main.cpp\
    imagemapper.cpp \
    marker.cpp \
    mapview.cpp \
    previewdialog.cpp \
    captureitem.cpp

HEADERS  += imagemapper.h \
    marker.h \
    mapview.h \
    previewdialog.h \
    captureitem.h

FORMS    += imagemapper.ui \
    previewdialog.ui
