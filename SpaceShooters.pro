TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/Enemy.cpp \
    src/Game.cpp \
    src/Graphics.cpp \
    src/Log.cpp \
    src/Main.cpp \
    src/Network.cpp \
    src/Object.cpp \
    src/ObjectParams.cpp \
    src/Player.cpp \
    src/TextureManager.cpp \
    src/Timer.cpp \
    src/Vector2D.cpp \
    src/Window.cpp \
    src/StateManager.cpp \
    src/InputManager.cpp \
    src/MenuState.cpp \
    src/MenuButton.cpp \
    src/PauseState.cpp \
    src/State.cpp \
    src/AnimatedGraphic.cpp \
    src/GameOverState.cpp \
    src/Layer.cpp \
    src/Level.cpp \
    src/LevelParser.cpp \
    src/TileLayer.cpp \
    src/common/base64/base64.cpp \
    src/ObjectLayer.cpp

LIBS +=  \
    -lSDL2 \
    -lSDL2_image \
    -lSDL2_mixer \
    -lSDL2_ttf \
    -lz \
    -ltinyxml2


HEADERS += \
    src/Defines.h \
    src/Enemy.h \
    src/Game.h \
    src/Graphics.h \
    src/Log.h \
    src/Network.h \
    src/Object.h \
    src/ObjectParams.h \
    src/Player.h \
    src/TextureManager.h \
    src/Timer.h \
    src/Vector2D.h \
    src/Window.h \
    src/WinState.h \
    src/StateManager.h \
    src/State.h \
    src/InputManager.h \
    src/MenuState.h \
    src/MenuButton.h \
    src/PauseState.h \
    src/AnimatedGraphic.h \
    src/GameOverState.h \
    src/Layer.h \
    src/Level.h \
    src/LevelParser.h \
    src/TileLayer.h \
    src/common/base64/base64.h \
    src/ObjectLayer.h

OTHER_FILES +=
