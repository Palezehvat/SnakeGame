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

qt_add_library(internals
    src/internalssettings.cpp
    inc/internalssettings.h
)

qt_add_library(controlsettings
    src/controlsettings.cpp
    inc/controlsettings.h
)

qt_add_library(gamesettings
    src/gamesettings.cpp
    inc/gamesettings.h
)

qt_add_library(keybindwidget
    src/keybindwidget.cpp
    inc/keybindwidget.h
)

qt_add_library(mainsettings
    src/mainsettings.cpp
    inc/mainsettings.h
)

qt_add_library(settings
    src/settings.cpp
    inc/settings.h
)

qt_add_library(mainwindow
    src/mainwindow.cpp
    inc/mainwindow.h
)

qt_add_library(panel
    src/gamepanel.cpp
    inc/gamepanel.h
)

qt_add_library(score
    src/score.cpp
    inc/score.h
)

qt_add_library(view
    src/gameview.cpp
    inc/gameview.h
)

qt_add_library(controller
    src/gamecontroller.cpp
    inc/gamecontroller.h
)

qt_add_library(appleWidget
    src/applewidget.cpp
    inc/applewidget.h
)

qt_add_library(uisettings
    src/uisettings.cpp
    inc/uisettings.h
)

add_library(app src/application.cpp)

target_link_libraries(logger PRIVATE spdlog::spdlog)
target_link_libraries(uisettings PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(mainsettings PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(keybindwidget PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(internals PRIVATE logger uisettings Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(gamesettings PRIVATE logger internals uisettings Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(controlsettings PRIVATE logger keybindwidget Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(settings PRIVATE logger gamesettings controlsettings mainsettings Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(appleWidget PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(score PRIVATE logger appleWidget uisettings Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(menu PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(food PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(snake PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(board PRIVATE logger Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(view PRIVATE logger board food snake Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(panel PRIVATE logger view score Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(controller PRIVATE logger settings panel score board food snake view Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(mainwindow PRIVATE logger panel menu settings controller Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(app PRIVATE mainwindow logger Qt6::Core Qt6::Gui Qt6::Widgets)

# ----- Main ----- #

add_executable(main main.cpp)
target_link_libraries(main PRIVATE app Qt6::Core Qt6::Gui Qt6::Widgets)