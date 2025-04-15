#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <iostream>
#include "gamecontroller.h"
#include "logger.h"

namespace Window {

class Application {
private:
    Control::ControlStates status();
    std::shared_ptr<spdlog::logger> logger;
    QApplication* app = nullptr;
    QMainWindow* mainWindow = nullptr;
    QPushButton* settings = nullptr;
    QPushButton* startGame = nullptr;
public:
    Application(int argc, char *argv[]) {
        Log::Logger::init();
        logger = Log::Logger::getLogger();
        app = new QApplication(argc, argv);
        if (!app) {
            logger->error("Ошибка инициализации QApplication!");
        }
    }

    void run();

private:
    void init(); 
    void handleEvents();
    void update();
    void render();
};

}

#endif // APPLICATION_H