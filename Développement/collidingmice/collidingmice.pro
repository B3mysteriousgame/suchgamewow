QT += widgets

HEADERS += \
	mouse.h \
    gamemanager.hpp \
    myview.hpp \
    perso.hpp \
    ball.hpp \
    angleoperation.hpp
SOURCES += \
	main.cpp \
        mouse.cpp \
    gamemanager.cpp \
    myview.cpp \
    perso.cpp \
    ball.cpp \
    angleoperation.cpp

RESOURCES += \
	mice.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/collidingmice
INSTALLS += target
