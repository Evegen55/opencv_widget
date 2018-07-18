#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T15:25:13
#
#-------------------------------------------------

QT       += core gui
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencv_widget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    actions_with_images.cpp

HEADERS += \
        mainwindow.h \
    actions_with_images.h

FORMS += \
        mainwindow.ui

RESOURCES += \
        fun.qrc

win32:INCLUDEPATH += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\include
win32:LIBS += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\x86\mingw\bin\libopencv_core331.dll
win32:LIBS += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\x86\mingw\bin\libopencv_highgui331.dll
win32:LIBS += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\x86\mingw\bin\libopencv_imgcodecs331.dll
win32:LIBS += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\x86\mingw\bin\libopencv_imgproc331.dll
win32:LIBS += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\x86\mingw\bin\libopencv_calib3d331.dll
win32:LIBS += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\x86\mingw\bin\libopencv_features2d331.dll
win32:LIBS += C:\Other_IT\opencv-3.3.1\for_experiments\build_3.3.1_with_qt_mingw_32_release\install\x86\mingw\bin\libopencv_videoio331.dll

unix:INCLUDEPATH += /usr/local/include
unix:LIBS += /usr/local/lib/libopencv_core.so.3.4.1
unix:LIBS += /usr/local/lib/libopencv_highgui.so.3.4.1
unix:LIBS += /usr/local/lib/libopencv_imgcodecs.so.3.4.1
unix:LIBS += /usr/local/lib/libopencv_imgproc.so.3.4.1
unix:LIBS += /usr/local/lib/libopencv_calib3d.so.3.4.1
unix:LIBS += /usr/local/lib/libopencv_features2d.so.3.4.1
unix:LIBS += /usr/local/lib/libopencv_videoio.so.3.4.1
