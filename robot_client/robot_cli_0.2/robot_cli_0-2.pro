TEMPLATE = app
QT += widgets network serialport
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
    singleton.h

SOURCES += main.cpp \
    mainwindow.cpp \
    apropos.cpp \
    server.cpp \
    central.cpp \
    terminal.cpp \
    singleton.cpp

FORMS +=
