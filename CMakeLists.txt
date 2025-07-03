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

add_library(logger STATIC src/logger.cpp)
set_target_properties(logger PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_library(board src/gameboard.cpp)

qt_add_library(snake
    src/snake.cpp
    inc/snake.h
)

qt_add_library(food
    src/food.cpp
    inc/food.h
)

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

qt_add_library(view
    src/gameview.cpp
    inc/gameview.h
)

qt_add_library(controller
    src/gamecontroller.cpp
    inc/gamecontroller.h
)

add_library(app src/application.cpp)

target_link_libraries(logger PRIVATE spdlog::spdlog)
target_link_libraries(settings PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(menu PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(food PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(snake PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(board PRIVATE logger settings Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(view PRIVATE logger settings board food snake Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(controller PRIVATE logger board food snake view Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(mainwindow PRIVATE logger view menu settings controller Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(app PRIVATE mainwindow logger Qt6::Core Qt6::Gui Qt6::Widgets)

# ----- Main ----- #

add_executable(main main.cpp)
target_link_libraries(main PRIVATE app Qt6::Core Qt6::Gui Qt6::Widgets)