#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <iostream>
#include "gamecontroller.h"
#include "logger.h"
#include "settings.h"
#include "mainmenu.h"
#include "gameview.h"


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
    std::shared_ptr<nGameView::GameView> board = nullptr;
    bool boardAdded = false;

private slots:
    void switchToSettings();
    void switchToGame();
    void switchToMenu();
};

};


#endif // MAINWINDOW_H