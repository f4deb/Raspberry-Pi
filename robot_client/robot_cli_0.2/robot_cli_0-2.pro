TEMPLATE = app
QT += widgets network
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += \
    mainwindow.h \
    apropos.h \
    setup.h \
    server.h \
    serialsettings.h \
    central.h \
    terminal.h

SOURCES += main.cpp \
    mainwindow.cpp \
    apropos.cpp \
    server.cpp \
    serialsettings.cpp \
    central.cpp \
    terminal.cpp
