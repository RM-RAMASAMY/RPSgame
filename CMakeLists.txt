# File: CMakeLists.txt

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

# Use qt_wrap_cpp to generate moc files
qt6_wrap_cpp(MOC_SOURCES ${HEADERS})

qt_add_executable(RPSGame
    ${HEADERS}
    ${SOURCES}
    ${MOC_SOURCES}
    ${UI_FILES}
)

target_link_libraries(RPSGame PRIVATE Qt6::Widgets)
