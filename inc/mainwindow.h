/**
 * @file mainwindow.h
 * @brief Основное окно приложения
 */

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

/**
 * @namespace nMainWindow
 * @brief Содержит в себе класс MainWindow
 */
namespace nMainWindow {
/**
 * @class MainWindow
 * @brief Класс обёртка над настройками, игрой и меню
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    MainWindow(QWidget* parent = nullptr);

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    QStackedWidget* stackedWidget = nullptr;
    std::shared_ptr<nMenu::Menu> menu = nullptr;
    std::shared_ptr<nSettings::Settings> settings = nullptr;
    std::shared_ptr<nGameController::GameController> controller = nullptr;
    std::shared_ptr<nGamePanel::GamePanel> panel = nullptr;
    bool firstGame = false;
    unsigned long long numberOfStartedGames = 0;

private slots:
    /// Сигнал для смены текущего виджета на настройки
    void switchToSettings();
    /// Сигнал для смены текущего виджета на игру
    void switchToGame();
    /// Сигнал для смены текущего виджета на меню
    void switchToMenu();
    /// Сигнал для смены текущего виджета на меню из игры
    void switchToMenuFromGame();
    /// Сигнал для смены текущего виджета на настройки
    void restartGame();
    /// Сигнал при окончания игры
    void onGameOver();

};

};


#endif // MAINWINDOW_H