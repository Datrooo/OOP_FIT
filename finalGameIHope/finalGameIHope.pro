QT       += core gui multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/entities/bullet.cpp \
    src/entities/enemy/enemy.cpp \
    src/entities/enemy/enemyfactory.cpp \
    src/entities/enemy/flyingenemy.cpp \
    src/entities/player/idlestate.cpp \
    src/entities/player/jumpingstate.cpp \
    src/entities/player/movingstate.cpp \
    src/entities/player/player.cpp \
    src/gamecontroller.cpp \
    src/gameview.cpp \
    src/interface/button.cpp \
    src/interface/gamescene.cpp \
    src/interface/losescene.cpp \
    src/interface/mainwindowscene.cpp \
    src/interface/platform.cpp \
    src/interface/settingsscene.cpp \
    src/interface/volumeslider.cpp \
    src/interface/winscene.cpp \
    src/soundcontroller.cpp \
    main.cpp


HEADERS += \
    include/entities/bullet.h \
    include/entities/direction.h \
    include/entities/enemy/baseenemy.h \
    include/entities/enemy/enemy.h \
    include/entities/enemy/enemyfactory.h \
    include/entities/enemy/flyingenemy.h \
    include/entities/entitytype.h \
    include/entities/hitable.h \
    include/entities/player/idlestate.h \
    include/entities/player/jumpingstate.h \
    include/entities/player/movingstate.h \
    include/entities/player/player.h \
    include/entities/player/playerstate.h \
    include/gamecontroller.h \
    include/gameview.h \
    include/interface/button.h \
    include/interface/gamescene.h \
    include/interface/losescene.h \
    include/interface/mainwindowscene.h \
    include/interface/platform.h \
    include/interface/settingsscene.h \
    include/interface/volumeslider.h \
    include/interface/winscene.h \
    include/soundcontroller.h


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
