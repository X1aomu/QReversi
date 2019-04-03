cmake_minimum_required(VERSION 3.1...3.14)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(QReversi)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    main.cc
    core/battle.cc
    core/gameplay.cc
    core/players/ai.cc
    core/players/human.cc
    core/players/virtualplayer.cc
    ui/mainwindow.cc
    ui/newgamedialog.cc
    ui/checkerboard/boardlayout.cc
    ui/checkerboard/checkerboardwidget.cc
    ui/checkerboard/boardgrid.cc
    ui/newgamedialog.ui
    resources.qrc
)

add_executable(qreversi ${SOURCES})
target_link_libraries(qreversi Qt5::Widgets)
