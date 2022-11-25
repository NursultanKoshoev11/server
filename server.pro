QT       += core gui
QT       += core network sql concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connect_db.cpp \
    main.cpp \
    mainwindow.cpp \
    myserver.cpp \
    mythread.cpp

HEADERS += \
    connect_db.h \
    mainwindow.h \
    myserver.h \
    mythread.h

FORMS += \
    connect_db.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
