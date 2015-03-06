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
    arme.h
=======
    barre.hpp
>>>>>>> e4f104a2297f8ae19c7f81cf4e80b55021f75adf
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
    arme.cpp
=======
    barre.cpp
>>>>>>> e4f104a2297f8ae19c7f81cf4e80b55021f75adf

RESOURCES += \
    mice.qrc \
    test.qrc

# install
target.path = ./suchGame
INSTALLS += target
