#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T02:38:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageMapper
TEMPLATE = app

# MS Media Foundation
LIBS += evr.lib
LIBS += mf.lib
LIBS += mfplat.lib
LIBS += Mfreadwrite.lib
LIBS += Mfuuid.lib
LIBS += Ole32.lib

# Socket API
LIBS += Ws2_32.lib

SOURCES += main.cpp\
    imagemapper.cpp \
    marker.cpp \
    camera.cpp \
    mapview.cpp \
    mpconnector.cpp \
    capturedevicedialog.cpp

HEADERS  += imagemapper.h \
    marker.h \
    camera.h \
    mapview.h \
    mpconnector.h \
    capturedevicedialog.h

FORMS    += imagemapper.ui \
    capturedevicedialog.ui
