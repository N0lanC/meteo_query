cmake_minimum_required(VERSION 3.17)
project(meteo_query)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)

add_executable(meteo_query main.cpp fenetre.cpp fenetre.h presenter.cpp presenter.h jute.cpp jute.h qcgaugewidget.cpp qcgaugewidget.h)
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets Network)
target_link_libraries(meteo_query Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

