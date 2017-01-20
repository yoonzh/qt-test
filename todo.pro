#-------------------------------------------------
#
# Project created by QtCreator 2017-01-19T13:53:26
#
#-------------------------------------------------

QT       += core gui
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = todo
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    task.cpp

HEADERS  += mainwindow.h \
    task.h

FORMS    += mainwindow.ui \
    task.ui
