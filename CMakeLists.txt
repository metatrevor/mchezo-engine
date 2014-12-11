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
    src/Network.cpp
    src/Network.h
    src/Object.cpp
    src/Object.h
    src/ObjectParams.cpp
    src/ObjectParams.h
    src/Player.cpp
    src/Player.h
    src/State.h
    src/StateEnums.h
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