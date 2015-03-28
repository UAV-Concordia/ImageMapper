#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T02:38:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageMapper
TEMPLATE = app

# ExifTool



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
    imagemarker.cpp \
    preferencesdialog.cpp

HEADERS  += imagemapper.h \
    marker.h \
    camera.h \
    mapview.h \
    mpconnector.h \
    imagemarker.h \
    preferencesdialog.h

FORMS    += imagemapper.ui \
    preferencesdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/release/ -lMetaWriter
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/debug/ -lMetaWriter
else:unix:!macx: LIBS += -L$$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/ -lMetaWriter

INCLUDEPATH += $$PWD/../MetaWriter/inc
INCLUDEPATH += $$PWD/../MetaWriter
DEPENDPATH += $$PWD/../MetaWriter/inc
DEPENDPATH += $$PWD/../MetaWriter

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/release/libMetaWriter.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/debug/libMetaWriter.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/release/MetaWriter.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/debug/MetaWriter.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../build-MetaWriter-Desktop_Qt_5_4_1_MSVC2013_32bit-Debug/libMetaWriter.a
