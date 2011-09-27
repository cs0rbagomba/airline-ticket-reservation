#-------------------------------------------------
#
# Project created by QtCreator 2011-09-23T18:46:43
#
#-------------------------------------------------

QT       += core \
            gui \
            xml \
            sql

TARGET   =  airline_seat_allocation_test

TEMPLATE =  app

CONFIG  += qtestlib

LIBS    += -lgcov
QMAKE_CXXFLAGS += -g -fprofile-arcs -ftest-coverage -O0
QMAKE_LDFLAGS += -g -fprofile-arcs -ftest-coverage  -O0

SOURCES +=  algorithmtests.cpp \
            mainwindow.cpp \
            airplanewidget.cpp \
            seat.cpp \
            database.cpp \
            filedatabase.cpp \
            sqldatabase.cpp

HEADERS  += algorithmtests.h \
            mainwindow.h \
            airplanewidget.h \
            seat.h \
            database.h \
            filedatabase.h \
            sqldatabase.h

FORMS    += mainwindow.ui
