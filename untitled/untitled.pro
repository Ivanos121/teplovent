QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets svg xml

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    draw_line.cpp \
    draw_poper.cpp \
    main.cpp \
    mainwindow.cpp \
    teplschem.cpp \
    trend.cpp \
    vvoddannie.cpp

HEADERS += \
    Base.h \
    draw_line.h \
    draw_poper.h \
    mainwindow.h \
    teplschem.h \
    trend.h \
    vvoddannie.h

FORMS += \
    draw_line.ui \
    draw_poper.ui \
    mainwindow.ui \
    teplschem.ui \
    trend.ui \
    vvoddannie.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
