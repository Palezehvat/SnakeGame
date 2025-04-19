#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPalette>
#include <QPixmap>
#include <iostream>
#include "gamecontroller.h"
#include "logger.h"

namespace nMainWindow {

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr);
    void showGame();
    void showSettings();

private:
    std::shared_ptr<spdlog::logger> logger;
    QPushButton* settings = nullptr;
    QPushButton* startGame = nullptr;

    void resizeEvent(QResizeEvent* event) override;;
};

};


#endif // MAINWINDOW_H