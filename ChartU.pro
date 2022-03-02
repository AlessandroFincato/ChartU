#-------------------------------------------------
#
# Project created by QtCreator 2021-12-23T17:54:02
#
#-------------------------------------------------

QT       += core gui
QT       += charts
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChartU
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
    Sources/main.cpp \
    Sources/MainWidget.cpp \
    Sources/Grafico.cpp \
    Sources/Istogramma.cpp \
    Sources/Areogramma.cpp \
    Sources/Cartesiano.cpp \
    Sources/Punto.cpp \
    Sources/Model.cpp \
    Sources/Controller.cpp

HEADERS += \
    Headers/MainWidget.h \
    Headers/Grafico.h \
    Headers/Istogramma.h \
    Headers/Areogramma.h \
    Headers/Cartesiano.h \
    Headers/Punto.h \
    Headers/Model.h \
    Headers/Controller.h
