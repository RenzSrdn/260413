QT += core gui widgets

CONFIG += c++17
CONFIG += sdk_no_version_check #serve per macOS

QMAKE_CXXFLAGS += -Wno-implicit-function-declaration #serve per macOS

TARGET = main
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    animal.h

FORMS += \
    mainwindow.ui