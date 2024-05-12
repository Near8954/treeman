cmake_minimum_required(VERSION 3.28)
project(treeman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(treeman main.cpp)
target_link_libraries(treeman
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

