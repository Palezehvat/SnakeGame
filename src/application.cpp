#include "application.h"

namespace nApplication {

    Application::Application(int argc, char *argv[]) {
        nLogger::Logger::init();
        logger = nLogger::Logger::getLogger();
        app = new QApplication(argc, argv);
        if (!app) {
            logger->error("Ошибка инициализации QApplication!");
        }
        logger->info("Класс Application успешно инициализирован");
    }

    void Application::run() {
        mainWindow = new nMainWindow::MainWindow();
        logger->info("Приложение успешно запущено");
        mainWindow->show();
        int result = app->exec();
        logger->info("Приложение завершено с кодом {}", result);
    }
}