# RaDoTech.pro
QT += core gui widgets printsupport
LIBS += -lqcustomplot


TARGET = radotech
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/userselection.cpp \
    src/profiletab.cpp \
    src/historytab.cpp \
    src/measurementtab.cpp \
    src/resultstab.cpp

HEADERS += \
    include/mainwindow.h \
    include/userselection.h \
    include/profiletab.h \
    include/historytab.h \
    include/measurementtab.h \
    include/resultstab.h \
    include/userdata.h

FORMS += \
    ui/mainwindow.ui \
    ui/userselection.ui \
    ui/profiletab.ui \
    ui/historytab.ui \
    ui/measurementtab.ui \
    ui/resultstab.ui

INCLUDEPATH += include/

UI_DIR = build/ui

OBJECTS_DIR = build/obj

MOC_DIR = build/moc

RCC_DIR = build/rcc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target