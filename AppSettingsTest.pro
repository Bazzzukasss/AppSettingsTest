QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
DESTDIR = ../bin

HEADERS += \
    src/Data.h \
    src/view.h

SOURCES += \
    src/main.cpp \
    src/view.cpp

INCLUDEPATH += \
    $$PWD/../AppSettingsLib/src \
    $$PWD/../SerializerLib/src

LIBS *= -L$$OUT_PWD/$$DESTDIR -lAppSettingsLib -lSerializerLib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
