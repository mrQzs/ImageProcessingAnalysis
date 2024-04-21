QT = core  gui
TARGET =  showImage
TEMPLATE = app

CONFIG += c++17 console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


INCLUDEPATH += $$PWD/3rdparty/OpenCV/include
LIBS += -L$$PWD/3rdparty/OpenCV/x64/mingw/lib
LIBS += -lopencv_core490.dll -lopencv_imgcodecs490.dll
LIBS += -lopencv_highgui490.dll -lopencv_imgproc490.dll -lopencv_photo490

SOURCES += \
    OpenCVHelper.cpp \
    main.cpp \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    OpenCVHelper.h
