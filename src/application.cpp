#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <iostream>
#include "application.h"
#include "logger.h"

namespace Window {
    void Application::init() {
        mainWindow = new QMainWindow();
        mainWindow->setWindowTitle("Snake game");
        mainWindow->resize(400, 300);
        
        startGame = new QPushButton("Start Game!", mainWindow);
        
        QWidget* centralWidget = new QWidget(mainWindow);
        mainWindow->setCentralWidget(centralWidget);

        QVBoxLayout* layout = new QVBoxLayout(centralWidget);
        layout->setAlignment(Qt::AlignCenter);

        layout->addWidget(startGame);
    }

    void Application::run() {
        init();
        logger->info("Приложение успешно запущено");
        mainWindow->show();
        int result = app->exec();
        logger->info("Приложение завершено с кодом {}", result);
    }

    void Application::handleEvents() {
        // Обработка событий
    }

    void Application::update() {
        // Логика обновлений
    }

    void Application::render() {
        // Рендеринг
    }
}
