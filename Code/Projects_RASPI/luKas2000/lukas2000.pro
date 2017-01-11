QT += widgets

TEMPLATE = app
QT -= core
TARGET = lukas2000


SOURCES += \
    Tests/test_hdmapi.c \
    hdmapi.c \
    main.cpp \
    mainwindow.cpp \
    LukasL/leftboard.cpp \
    LukasC/centerboard.cpp \
    LukasC/error_left.cpp \
    LukasC/error_right.cpp \
    LukasC/us_center.cpp \
    LukasR/rightboard.cpp \
    LukasR/printer.cpp \
    LukasR/camera.cpp \
    Size/size.cpp \
    maincontroller.cpp \
    Tests/test_1.cpp \
    Tests/test_2.cpp \
    Tests/test_3.cpp

HEADERS += \
    Tests/test_hdmapi.h \
    hdmapi.h \
    mainwindow.hpp \
    LukasL/leftboard.hpp \
    LukasC/centerboard.hpp \
    LukasC/error_left.hpp \
    LukasC/error_right.hpp \
    LukasC/us_center.hpp \
    LukasR/rightboard.hpp \
    LukasR/printer.hpp \
    LukasR/camera.hpp \
    Size/size.hpp \
    maincontroller.hpp \
    Tests/test_1.hpp \
    Tests/test_2.hpp \
    Tests/test_3.hpp

RESOURCES += \
    images.qrc
