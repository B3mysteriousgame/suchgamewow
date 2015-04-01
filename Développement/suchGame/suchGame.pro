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
    strategie.hpp

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
    strat2.cpp

RESOURCES += \
    mice.qrc \
    test.qrc

# install
target.path = ./suchGame
INSTALLS += target
