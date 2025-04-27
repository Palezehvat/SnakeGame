#include "mainwindow.h"

namespace nMainWindow {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setWindowTitle("Snake game");
    this->resize(400, 300);
    stackedWidget = new QStackedWidget();
    setCentralWidget(stackedWidget);

    menu = new nMenu::Menu();
    settings = new nSettings::Settings();
    game = new nGameBoard::GameBoard(); //

    stackedWidget->addWidget(menu);
    stackedWidget->addWidget(settings);
    stackedWidget->addWidget(game); //

    stackedWidget->setCurrentWidget(menu);

    connect(menu, &nMenu::Menu::switchToSettings, this, &MainWindow::switchToSettings);
    connect(settings, &nSettings::Settings::switchToMenu, this, &MainWindow::switchToMenu);
    connect(menu, &nMenu::Menu::switchToGame, this, &MainWindow::switchToGame);
}

void MainWindow::switchToSettings() {
    stackedWidget->setCurrentWidget(settings);
}

void MainWindow::switchToMenu() {
    stackedWidget->setCurrentWidget(menu);
}

void MainWindow::switchToGame() {
    game->createBoard(); //
    stackedWidget->setCurrentWidget(game); //
}

}
