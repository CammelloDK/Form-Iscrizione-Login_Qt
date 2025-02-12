QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    elenco.cpp \
    grafici.cpp \
    iscrizione.cpp \
    loginadmin.cpp \
    loginusr.cpp \
    main.cpp \
    mainwindow.cpp \
    recupero.cpp

HEADERS += \
    elenco.h \
    grafici.h \
    iscrizione.h \
    loginadmin.h \
    loginusr.h \
    mainwindow.h \
    recupero.h

FORMS += \
    elenco.ui \
    grafici.ui \
    iscrizione.ui \
    loginadmin.ui \
    loginusr.ui \
    mainwindow.ui \
    recupero.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
