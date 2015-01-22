QT += widgets

HEADERS += \
    mouse.h \
    gamemanager.hpp \
    myview.hpp \
    perso.hpp \
    ball.hpp \
    angleoperation.hpp \
    patate.hpp
SOURCES += \
    main.cpp \
    mouse.cpp \
    gamemanager.cpp \
    myview.cpp \
    perso.cpp \
    ball.cpp \
    angleoperation.cpp \
    patate.cpp

RESOURCES += \
    mice.qrc \
    test.qrc

# install
target.path = ./suchGame
INSTALLS += target
