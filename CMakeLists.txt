cmake_minimum_required(VERSION 3.15)

project(Snake VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(spdlog REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(inc)

# ----- Modules ----- #

add_library(model src/snake.cpp src/food.cpp)
add_library(logger STATIC src/logger.cpp)
set_target_properties(logger PROPERTIES POSITION_INDEPENDENT_CODE ON)

qt_add_library(menu
    src/mainmenu.cpp
    inc/mainmenu.h
)

qt_add_library(settings
    src/settings.cpp
    inc/settings.h
)

qt_add_library(mainwindow
    src/mainwindow.cpp
    inc/mainwindow.h
)

add_library(app src/application.cpp)
add_library(controller src/gamecontroller.cpp)

target_link_libraries(logger PRIVATE spdlog::spdlog)
target_link_libraries(menu PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(settings PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(mainwindow PRIVATE logger menu settings Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(app PRIVATE controller mainwindow logger Qt6::Core Qt6::Gui Qt6::Widgets)

# ----- Main ----- #

add_executable(main main.cpp)
target_link_libraries(main PRIVATE app model Qt6::Core Qt6::Gui Qt6::Widgets)