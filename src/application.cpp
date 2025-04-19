#include "application.h"

namespace nApplication {
    void Application::run() {
        mainWindow = new nMainWindow::MainWindow();
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