#include "mainwindow.h"

namespace nMainWindow {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    logger = Log::Logger::getLogger();
    
    stackedWidget = new QStackedWidget();
    setCentralWidget(stackedWidget);
    menu = std::make_shared<nMenu::Menu>();
    settings = std::make_shared<nSettings::Settings>();
    controller = std::make_shared<nGameController::GameController>(settings);
    
    unsigned int sizeCell = UISettings::currentSizeCell;
    unsigned int gameWidth = UISettings::maxWidth * sizeCell;
    unsigned int gameHeight = UISettings::maxHeight * sizeCell;
    int windowWidth = gameWidth * 4 / 3;

    this->resize(windowWidth, gameHeight);

    firstGame = false;
    numberOfStartedGames = 0;

    stackedWidget->addWidget(menu.get());
    stackedWidget->addWidget(settings.get());

    stackedWidget->setCurrentWidget(menu.get());

    connect(menu.get(), &nMenu::Menu::switchToSettings, this, &MainWindow::switchToSettings);
    connect(settings.get(), &nSettings::Settings::switchToMenu, this, &MainWindow::switchToMenu);
    connect(menu.get(), &nMenu::Menu::switchToGame, this, &MainWindow::switchToGame);
    connect(controller.get(), &nGameController::GameController::gameOver, this, &MainWindow::onGameOver);
    logger->info("Класс MainWindow успешно инициализирован");
}

void MainWindow::switchToSettings() {
    stackedWidget->setCurrentWidget(settings.get());
    logger->info("Успешная смена окна на настройки");
}

void MainWindow::switchToMenu() {
    stackedWidget->setCurrentWidget(menu.get());
    logger->info("Успешная смена окна на меню");
}

void MainWindow::switchToGame() {
    unsigned int height = settings->getHeight();
    unsigned int width = settings->getWidth();
    numberOfStartedGames += 1;

    if (!firstGame) {
        panel = controller->startGame();
        stackedWidget->addWidget(panel.get());
        firstGame = true;

        connect(panel.get(), &nGamePanel::GamePanel::backToMenu,
            this, &MainWindow::switchToMenuFromGame);

        connect(panel.get(), &nGamePanel::GamePanel::restartGame,
            this, &MainWindow::restartGame);
    } else {
        controller->restart();
    }
    stackedWidget->setCurrentWidget(panel.get());
    logger->info(fmt::format("Успешная смена окна на игру. Номер запущенной игры: {}",
            std::to_string(numberOfStartedGames)));
}

void MainWindow::onGameOver() {
    logger->info("Получен сигнал gameOver");
}

void MainWindow::switchToMenuFromGame() {
    stackedWidget->setCurrentWidget(menu.get());
    logger->info("Возврат в главное меню из игры");
}

void MainWindow::restartGame() {
    numberOfStartedGames += 1;
    controller->restart();
    logger->info(fmt::format("Запуск игры номер {}", std::to_string(numberOfStartedGames)));
}

}
