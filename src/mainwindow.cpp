#include "mainwindow.h"

namespace nMainWindow {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    logger = Log::Logger::getLogger();
    this->setWindowTitle("Snake game");
    this->resize(400, 300);
    stackedWidget = new QStackedWidget();
    setCentralWidget(stackedWidget);
    menu = std::make_shared<nMenu::Menu>();
    settings = std::make_shared<nSettings::Settings>();
    controller = std::make_shared<nGameController::GameController>();

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
    controller->startGame();
    board = controller->getBoard();

    if (!boardAdded) {
        stackedWidget->addWidget(board.get());
        boardAdded = true;

        connect(board.get(), &nGameView::GameView::backToMenu,
            this, &MainWindow::switchToMenuFromGame);

        connect(board.get(), &nGameView::GameView::restartGame,
            this, &MainWindow::switchToGame);
    }

    stackedWidget->setCurrentWidget(board.get());
    logger->info("Успешная смена окна на игру");
}

void MainWindow::onGameOver() {
    logger->info("Получен сигнал gameOver");
}

void MainWindow::switchToMenuFromGame() {
    stackedWidget->setCurrentWidget(menu.get());
    logger->info("Возврат в главное меню из игры");
}

}
