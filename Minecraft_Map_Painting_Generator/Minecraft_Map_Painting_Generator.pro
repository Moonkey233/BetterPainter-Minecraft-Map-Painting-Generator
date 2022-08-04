QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = Minecraft Map Painting Generator designed by Moonkey_ 2022
RC_FILE = logo.rc

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mbeginform.cpp \
    mcolor.cpp \
    meditform.cpp \
    mfinishform.cpp \
    moutputdialog.cpp \
    mpainting.cpp \
    mpicture.cpp \
    msettingdialog.cpp

HEADERS += \
    data.h \
    mainwindow.h \
    mbeginform.h \
    mcolor.h \
    meditform.h \
    mfinishform.h \
    moutputdialog.h \
    mpainting.h \
    mpicture.h \
    msettingdialog.h

FORMS += \
    mainwindow.ui \
    mbeginform.ui \
    meditform.ui \
    mfinishform.ui \
    moutputdialog.ui \
    msettingdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
