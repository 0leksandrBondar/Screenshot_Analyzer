cmake_minimum_required(VERSION 3.14)

project(ScreenAnalizer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Sql REQUIRED)

include_directories(${ImageMagick_INCLUDE_DIRS})

add_subdirectory(app)
