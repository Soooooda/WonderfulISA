QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/Decode.cpp \
    ../src/Execute.cpp \
    ../src/Fetch.cpp \
    ../src/MemoryAccess.cpp \
    ../src/PipeLine.cpp \
    ../src/Register.cpp \
    ../src/Stage.cpp \
    ../src/WriteBack.cpp \
    ../src/cache.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp \
    ../src/simulator.cpp

HEADERS += \
    ../include/Decode.h \
    ../include/Execute.h \
    ../include/Fetch.h \
    ../include/MemoryAccess.h \
    ../include/PipeLine.hpp \
    ../include/Register.h \
    ../include/Stage.h \
    ../include/WriteBack.h \
    ../include/cache.hpp \
    ../include/mainwindow.h \
    ../include/simulator.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
