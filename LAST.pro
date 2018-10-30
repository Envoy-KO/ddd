#-------------------------------------------------
#
# Project created by QtCreator 2017-04-03T14:39:09
#
#-------------------------------------------------

QT       += core gui
QT          += opengl
QT          +=network
QT       += multimedia
QT       += multimediawidgets
QT       += widgets
QT       += core
QT       += axcontainer
QT       += widgets
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LAST
TEMPLATE = app

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS

INCLUDEPATH +=D:\QT\20170403\LAST\chart\include
LIBS +=D:\QT\20170403\lib\chartdir51.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    OpenGL/glwidget.cpp \
    car/car.cpp \
    textwidget/textwidget.cpp \
    Dashboard/dashboard.cpp \
    chart/mychart.cpp \
    chart/curve/chistogram.cpp \
    chart/curve/clinechart.cpp \
    chart/curve/cpiechart.cpp \
    chart/curve/qchartviewer.cpp \
    Max/maxwidget.cpp

HEADERS  += mainwindow.h \
    OpenGL/glwidget.h \
    car/car.h \
    textwidget/textwidget.h \
    Dashboard/dashboard.h \
    chart/mychart.h \
    chart/curve/chistogram.h \
    chart/curve/clinechart.h \
    chart/curve/cpiechart.h \
    chart/curve/qchartviewer.h \
    Max/maxwidget.h



LIBS += -lopengl32 \
    -lglu32 \
    -lglut \

RESOURCES += \
    Images/images.qrc

DISTFILES +=
