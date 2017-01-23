#-------------------------------------------------
#
# Project created by QtCreator 2017-01-20T14:33:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysinfo
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    sysinfo.cpp

HEADERS  += mainwindow.h \
    sysinfo.h

windows {
    SOURCES += sysinfowindowsimpl.cpp
    HEADERS += sysinfowindowsimpl.h
}

linux {
    SOURCES += sysinfolinuximpl.cpp
    HEADERS += sysinfolinuximpl.h
}

macx {
    SOURCES += sysinfomacimpl.cpp
    HEADERS += sysinfomacimpl.h
}

FORMS    += mainwindow.ui
