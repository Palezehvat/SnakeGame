#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "gamecontroller.h"
#include "logger.h"

namespace nApplication {

class Application {
private:
    nControlStates::ControlStates status();
    std::shared_ptr<spdlog::logger> logger;
    QApplication* app = nullptr;
    nMainWindow::MainWindow* mainWindow = nullptr;
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
    void handleEvents();
    void update();
    void render();
};

}

#endif // APPLICATION_H