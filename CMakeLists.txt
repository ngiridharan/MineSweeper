cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Minesweeper)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "C:/Users/nikgi/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
add_executable(Minesweeper main.cpp board.h board.cpp tile.h tile.cpp TextureManager.h TextureManager.cpp Random.cpp Random.h GameManager.cpp GameManager.h)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)