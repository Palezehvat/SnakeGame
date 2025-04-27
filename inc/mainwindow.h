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
    nMenu::Menu* menu = nullptr;
    nSettings::Settings* settings = nullptr;
    nGameBoard::GameBoard* game = nullptr;

private slots:
    void switchToSettings();
    void switchToGame();
    void switchToMenu();
};

};


#endif // MAINWINDOW_H