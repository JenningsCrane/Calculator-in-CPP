QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += ../src

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/symbolStruct.cc \
    ../src/calcParser.cc \
    ../src/calcExpression.cc \
    ../src/calcModel.cc \
    ../src/calcController.cc \
    ../src/main.cc \
    ../src/mainwindow.cc \
    ../src/qcustomplot.cc

HEADERS += \
    ../src/symbolStruct.h \
    ../src/calcParser.h \
    ../src/calcExpression.h \
    ../src/calcModel.h \
    ../src/calcController.h \
    ../src/mainwindow.h \
    ../src/qcustomplot.h

FORMS += \
    ../src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
