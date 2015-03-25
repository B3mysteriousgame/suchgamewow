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
<<<<<<< HEAD
    arme.h \
    barre.hpp \
    map.h \
    element.h
=======
    myscene.hpp \
    arme.h \
    barre.hpp
>>>>>>> a6968f8cd1cecf71169b410da489be68fcf64a49

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
<<<<<<< HEAD
    arme.cpp \
    barre.cpp \
    map.cpp \
    element.cpp
=======
    myscene.cpp \
    arme.cpp \
    barre.cpp
>>>>>>> a6968f8cd1cecf71169b410da489be68fcf64a49

RESOURCES += \
    mice.qrc \
    test.qrc

# install
target.path = ./suchGame
INSTALLS += target
