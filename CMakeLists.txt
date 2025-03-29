cmake_minimum_required(VERSION 3.14)
project(RPSGame)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

set(UI_FILES
    mainwindow.ui
)

qt6_wrap_ui(WRAP_UI ${UI_FILES})
qt6_wrap_cpp(WRAP_CPP ${HEADERS})

add_executable(RPSGame
    ${SOURCES}
    ${HEADERS}
    ${WRAP_UI}
    ${WRAP_CPP}
)

target_link_libraries(RPSGame PRIVATE Qt6::Widgets)
