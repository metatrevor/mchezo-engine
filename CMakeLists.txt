cmake_minimum_required(VERSION 2.8.4)
project(Mchezo-engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Defines.h
    src/AnimatedGraphic.cpp
    src/AnimatedGraphic.h
    src/Enemy.cpp
    src/Enemy.h
    src/Game.cpp
    src/Game.h
    src/GameOverState.cpp
    src/GameOverState.h
    src/InputManager.cpp
    src/InputManager.h
    src/Layer.cpp
    src/Layer.h
    src/Level.h
    src/Level.cpp
    src/LevelParser.h
    src/LevelParser.cpp
    src/Log.cpp
    src/Log.h
    src/Main.cpp
    src/MenuButton.cpp
    src/MenuButton.h
    src/MenuState.cpp
    src/MenuState.h
    src/Network.cpp
    src/Network.h
    src/Object.cpp
    src/Object.h
    src/ObjectLayer.h
    src/ObjectLayer.cpp
    src/ObjectParams.cpp
    src/ObjectParams.h
    src/PauseState.cpp
    src/PauseState.h
    src/Player.cpp
    src/Player.h
    src/State.h
    src/State.cpp
    src/StateManager.cpp
    src/StateManager.h
    src/TextureManager.cpp
    src/TextureManager.h
    src/Timer.cpp
    src/Timer.h
    src/TileLayer.h
    src/TileLayer.cpp
    src/Vector2D.cpp
    src/Vector2D.h
    src/Window.cpp
    src/Window.h
    src/WinState.h
    #Common library
    src/common/base64/base64.h
    src/common/base64/base64.cpp
    )

add_executable(Mchezo-engine ${SOURCE_FILES})
find_package (ZLIB)


include (cmake/FindTinyXML2.cmake)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED)
PKG_SEARCH_MODULE(TINYXML2 REQUIRED tinyxml2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIRS} ${TINYXML2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${ZLIB_LIBRARIES} ${TINYXML2_LIBRARY})