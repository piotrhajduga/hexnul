cmake_minimum_required (VERSION 3.7)
project (hexnul)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++11")

#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#PKG_SEARCH_MODULE(SDL2_image REQUIRED SDL2_image)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories (${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
include_directories ("${PROJECT_SOURCE_DIR}/inc")

add_executable(${PROJECT_NAME} src/main.cpp
    src/utils.cpp
    src/sprite.cpp
    src/world.cpp
    src/gamestate.cpp
    src/worldstate.cpp
    src/maploader.cpp
    src/building.cpp
    src/road.cpp
    src/thing.cpp
    src/tile.cpp
    src/agent.cpp
    src/toolbar.cpp
    src/game.cpp
    )

target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
