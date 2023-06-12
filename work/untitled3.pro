QT       += core gui
QT       += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    choose.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    netwindow.cpp \
    networkdata.cpp \
    networkserver.cpp \
    networksocket.cpp \
    setting.cpp \
    start.cpp

HEADERS += \
    block.h \
    choose.h \
    item.h \
    mainwindow.h \
    netwindow.h \
    networkdata.h \
    networkserver.h \
    networksocket.h \
    setting.h \
    start.h \
    variable.h

FORMS += \
    choose.ui \
    mainwindow.ui \
    netwindow.ui \
    setting.ui \
    start.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    record.qrc \
    source.qrc

DISTFILES += \
    a.txt



