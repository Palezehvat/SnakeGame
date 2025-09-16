/**
 * @file application.h
 * @brief Отрисовка яблока и количество съеденных яблок 
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "logger.h"

/**
 * @namespace nApplication
 * @brief Содержит в себе класс Application
 */
namespace nApplication {
/**
 * @class Application
 * @brief Класс для обёртки QApplication
 */
class Application {

public:
    /**
     * @brief Конструктор
     * @param argc количество аргументов(для QApplication)
     */
    Application(int argc, char* argv[]);
    /// Запуск приложения, основная функция
    void run();

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    QApplication* app = nullptr;
    nMainWindow::MainWindow* mainWindow = nullptr;
};

}

#endif // APPLICATION_H