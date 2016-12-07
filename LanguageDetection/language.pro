QT += core
QT -= gui

CONFIG += c++11

TARGET = language
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    training_text_map.cpp \
    language_score_model.cpp \
    language_detector.cpp

HEADERS += \
    training_text_map.h \
    language_score_model.h \
    language_detector.h
