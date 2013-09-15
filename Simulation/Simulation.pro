#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T21:11:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simulation
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    detectordialog.cpp \
    inputdefaultfile.cpp

HEADERS  += dialog.h \
    detectordialog.h \
    inputdefaultfile.h \
    parmdefine.h

FORMS    += \
    psfDialog.ui \
    detectorDialog.ui

RESOURCES     = simulation.qrc
