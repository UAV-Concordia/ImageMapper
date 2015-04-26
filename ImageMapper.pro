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
    mapview.cpp \
    previewdialog.cpp \
    entry.cpp \
    entrytableitem.cpp \
    entrymarker.cpp

HEADERS  += imagemapper.h \
    mapview.h \
    previewdialog.h \
    entry.h \
    entrymediator.h \
    entrytableitem.h \
    entrymarker.h

FORMS    += imagemapper.ui \
    previewdialog.ui
