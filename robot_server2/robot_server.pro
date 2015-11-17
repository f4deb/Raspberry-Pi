QT += widgets network serialport

TARGET = terminal
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += mainwindow.h \
    robot_uart.h \
    settingsdialog.h \
    console.h

SOURCES += mainwindow.cpp main.cpp \
    robot_uart.cpp \
    settingsdialog.cpp \
    console.cpp

FORMS += \
    settingsdialog.ui
