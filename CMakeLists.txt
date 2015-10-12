cmake_minimum_required(VERSION 2.8.4)
project(Mchezo-engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/Mchezo/Defines.h
        src/Mchezo/AnimatedGraphic.cpp
        src/Mchezo/AnimatedGraphic.h
        src/starter/Enemy.cpp
        src/starter/Enemy.h
        src/starter/Game.cpp
        src/starter/Game.h
        src/starter/GameOverState.cpp
        src/starter/GameOverState.h
        src/Mchezo/InputManager.cpp
        src/Mchezo/InputManager.h
        src/Mchezo/Layer.cpp
        src/Mchezo/Layer.h
        src/Mchezo/Level.h
        src/Mchezo/Level.cpp
        src/Mchezo/Log.cpp
        src/Mchezo/Log.h
        src/starter/Main.cpp
        src/Mchezo/MenuButton.cpp
        src/Mchezo/MenuButton.h
        src/starter/MenuState.cpp
        src/starter/MenuState.h
        src/Mchezo/Object.cpp
        src/Mchezo/Object.h
        src/starter/PauseState.cpp
        src/starter/PauseState.h
        src/starter/Player.cpp
        src/starter/Player.h
        src/Mchezo/SoundManager.h
        src/Mchezo/SoundManager.cpp
        src/Mchezo/State.h
        src/Mchezo/State.cpp
        src/Mchezo/StateManager.cpp
        src/Mchezo/StateManager.h
        src/Mchezo/TextureManager.cpp
        src/Mchezo/TextureManager.h
        src/Mchezo/Timer.cpp
        src/Mchezo/Timer.h
        src/Mchezo/TileLayer.h
        src/Mchezo/TileLayer.cpp
        src/Mchezo/Vector2D.cpp
        src/Mchezo/Vector2D.h
        src/Mchezo/Window.cpp
        src/Mchezo/Window.h
    #Common library
    )

add_executable(Mchezo-engine ${SOURCE_FILES})


include (cmake/FindTinyXML2.cmake)
include (cmake/FindSDL2_mixer.cmake)
include (cmake/FindTmxParser.cmake)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED)
PKG_SEARCH_MODULE(TINYXML2 REQUIRED tinyxml2)
PKG_SEARCH_MODULE(TMXPARSER REQUIRED tmx-parser)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS}
                    ${SDL2_TTF_INCLUDE_DIRS} ${TINYXML2_INCLUDE_DIR} ${SDL2_Mixer_INCLUDE_DIRS}
                    ${TMXPARSER_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES}
                      ${SDL2IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES}
                      ${TINYXML2_LIBRARY} ${SDLMIXER_LIBRARY} ${TMXPARSER_LIBRARY})