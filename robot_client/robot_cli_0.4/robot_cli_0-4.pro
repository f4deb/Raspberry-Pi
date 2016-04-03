TEMPLATE = app
QT += widgets network serialport printsupport
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += \
    mainwindow.h \
    apropos.h \
    setup.h \
    server.h \
    central.h \
    terminal.h \
    singleton.h \
    mpu.h \
    ../../Qt-custom-gauge-widget-master/source/qcgaugewidget.h \
    ../../qcustomplot/qcustomplot.h

SOURCES += main.cpp \
    mainwindow.cpp \
    apropos.cpp \
    server.cpp \
    terminal.cpp \
    singleton.cpp \
    central.cpp \
    mpu.cpp \
    ../../Qt-custom-gauge-widget-master/source/qcgaugewidget.cpp \
    ../../qcustomplot/qcustomplot.cpp

FORMS +=
