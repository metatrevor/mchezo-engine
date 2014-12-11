cmake_minimum_required(VERSION 2.8.4)
project(SpaceShooters)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Defines.h
    src/Enemy.cpp
    src/Enemy.h
    src/Game.cpp
    src/Game.h
    src/Graphics.cpp
    src/Graphics.h
    src/InputManager.cpp
    src/InputManager.h
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
    src/ObjectParams.cpp
    src/ObjectParams.h
    src/Player.cpp
    src/Player.h
    src/State.h
    src/StateManager.cpp
    src/StateManager.h
    src/TextureManager.cpp
    src/TextureManager.h
    src/Timer.cpp
    src/Timer.h
    src/Vector2D.cpp
    src/Vector2D.h
    src/Window.cpp
    src/Window.h
    src/WinState.h)

add_executable(SpaceShooters ${SOURCE_FILES})
find_package (Threads)
add_executable(chatserver ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries (chatserver ${CMAKE_THREAD_LIBS_INIT})


INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})