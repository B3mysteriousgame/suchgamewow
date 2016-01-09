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
    ennemylopette.h \
    simpleanim.hpp \
    statsmanager.hpp \
    highlighteffect.hpp \
    coffre.hpp \
    longsword.h \
    dragonsword.hpp \
    inventaire.hpp \
    obstacle.h \
    popup.hpp \
    dragon.hpp \
    patate.hpp \
    panel.hpp \
    kianim.h \
    aspritemanager.hpp \
    kispritemanager.hpp \
    item.hpp \
    potion.hpp

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
    ennemylopette.cpp \
    simpleanim.cpp \
    statsmanager.cpp \
    highlighteffect.cpp \
    coffre.cpp \
    longsword.cpp \
    dragonsword.cpp \
    inventaire.cpp \
    obstacle.cpp\
    popup.cpp \
    dragon.cpp \
    panel.cpp \
    kianim.cpp \
    aspritemanager.cpp \
    kispritemanager.cpp \
    item.cpp \
    potion.cpp

RESOURCES += \
    sprites.qrc

# install
target.path = ./suchGame
INSTALLS += target

OTHER_FILES += \
    images/MapTest.png \
    images/MapTest1.png

static { # everything below takes effect with CONFIG ''= static
    CONFIG += static
    CONFIG += staticlib # this is needed if you create a static library, not a static executable
    DEFINES+= STATIC
    message("~~~ static build ~~~") # this is for information, that the static build is done
    mac: TARGET = $$join(TARGET,,,_static)
#this adds an _static in the end, so you can seperate static build
#from non static build
    win32: TARGET = $$join(TARGET,,,s)
#this adds an s in the end, so you can seperate static build from
#non static build
}
