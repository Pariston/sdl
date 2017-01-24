cmake_minimum_required(VERSION 3.6)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES headers/Bird.h classes/Bird.cpp classes/Game.cpp headers/Game.h headers/GameSettings.h Main.cpp classes/Message.cpp headers/Message.h classes/Pipe.cpp headers/Enemy.h classes/Enemy.cpp headers/Bullet.h classes/Bullet.cpp)
add_executable(untitled ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TFF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})