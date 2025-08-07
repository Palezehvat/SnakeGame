#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <iostream>
#include "gamecontroller.h"
#include "logger.h"
#include "settings.h"
#include "mainmenu.h"
#include "gamepanel.h"
#include "uisettings.h"


namespace nMainWindow {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    std::shared_ptr<spdlog::logger> logger;
    QStackedWidget* stackedWidget;
    std::shared_ptr<nMenu::Menu> menu = nullptr;
    std::shared_ptr<nSettings::Settings> settings = nullptr;
    std::shared_ptr<nGameController::GameController> controller = nullptr;
    std::shared_ptr<nGamePanel::GamePanel> panel = nullptr;
    bool firstGame;
    unsigned long long numberOfStartedGames;

private slots:
    void switchToSettings();
    void switchToGame();
    void switchToMenu();
    void switchToMenuFromGame();
    void restartGame();
    void onGameOver();

};

};


#endif // MAINWINDOW_H