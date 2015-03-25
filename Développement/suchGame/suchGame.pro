QT += widgets

HEADERS += \
    mouse.h \
    gamemanager.hpp \
    myview.hpp \
    perso.hpp \
    ball.hpp \
    angleoperation.hpp \
    patate.hpp \
    personnage.hpp \
    ennemy.hpp \
    strat1.hpp \
    strat2.hpp \
    strategie.hpp \
    movefreelystrat.hpp \
    ennemyfactory.h \
    myscene.hpp \
    arme.h \
    barre.hpp

SOURCES += \
    main.cpp \
    mouse.cpp \
    gamemanager.cpp \
    myview.cpp \
    perso.cpp \
    ball.cpp \
    angleoperation.cpp \
    patate.cpp \
    ennemy.cpp \
    personnage.cpp \
    strat1.cpp \
    strat2.cpp \
    movefreelystrat.cpp \
    ennemyfactory.cpp \
    myscene.cpp \
    arme.cpp \
    barre.cpp

RESOURCES += \
    mice.qrc \
    test.qrc

# install
target.path = ./suchGame
INSTALLS += target
