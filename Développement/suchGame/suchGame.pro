QT += widgets

HEADERS += \
    angleoperation.hpp \
    arme.h \
    ball.hpp \
    barre.hpp \
    ennemy.hpp \
    gamemanager.hpp \
    map.h \
    mouse.h \
    movefreelystrat.hpp \
    myscene.hpp \
    myview.hpp \
    patate.hpp \
    perso.hpp \
    personnage.hpp \
    strat1.hpp \
    strat2.hpp \
    ennemyfactory.h \
    strategie.hpp \
    spritemanager.hpp \
    simpleanim.hpp \
    statsframe.hpp

SOURCES += \
    angleoperation.cpp \
    arme.cpp \
    ball.cpp \
    barre.cpp \
    ennemy.cpp \
    ennemyfactory.cpp \
    gamemanager.cpp \
    main.cpp \
    map.cpp \
    mouse.cpp \
    movefreelystrat.cpp \
    myview.cpp \
    myscene.cpp \
    patate.cpp \
    perso.cpp \
    personnage.cpp \
    strat1.cpp \
    strat2.cpp \
    spritemanager.cpp \
    simpleanim.cpp \
    statsframe.cpp

RESOURCES += \
    mice.qrc \
    sprites.qrc

# install
target.path = ./suchGame
INSTALLS += target

OTHER_FILES += \
    images/MapTest.png \
    images/MapTest1.png
