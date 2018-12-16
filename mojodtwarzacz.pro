#-------------------------------------------------
#
# Project created by QtCreator 2018-11-10T00:29:57
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mojodtwarzacz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addnew.cpp \
    step.cpp \
    name.cpp

HEADERS  += mainwindow.h \
    addnew.h \
    step.h \
    name.h

FORMS    += mainwindow.ui \
    addnew.ui \
    step.ui \
    name.ui
