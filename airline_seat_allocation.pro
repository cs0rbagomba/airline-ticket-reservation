#-------------------------------------------------
#
# Project created by QtCreator 2011-09-23T18:46:43
#
#-------------------------------------------------

QT       += core \
            gui \
            xml \
            sql

TARGET   =  airline_seat_allocation
TEMPLATE =  app


SOURCES +=  main.cpp \
            mainwindow.cpp \
            airplanewidget.cpp \
            seat.cpp \
            database.cpp \
            filedatabase.cpp \
            sqldatabase.cpp

HEADERS  += mainwindow.h \
            airplanewidget.h \
            seat.h \
            database.h \
            filedatabase.h \
            sqldatabase.h

FORMS    += mainwindow.ui
