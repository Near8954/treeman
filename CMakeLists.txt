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

add_executable(treeman main.cpp
        src/interface/App/App.cpp
        src/interface/App/App.h
        src/interface/Canvas/Canvas.cpp
        src/interface/Canvas/Canvas.h
        src/trees/Node.h
        src/trees/CartesianTree/CartesianTree.cpp
        src/trees/CartesianTree/CartesianTree.h
        src/header.h
        src/trees/SplayTree/SplayTree.h
        src/trees/SplayTree/SplayTree.cpp
        src/trees/AvlTree/AvlTree.cpp
        src/trees/AvlTree/AvlTree.h
)
target_link_libraries(treeman
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

