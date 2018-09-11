TEMPLATE = app
CONFIG += console c++11 thread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    tcpserver.cpp \
    mastersocket.cpp

HEADERS += \
    tcpserver.h \
    mastersocket.h
