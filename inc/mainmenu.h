#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCoreApplication>
#include "logger.h"

namespace nMenu {

class Menu : public QWidget {
    Q_OBJECT

public:
    Menu(QWidget* parent = nullptr);

private:
    std::shared_ptr<spdlog::logger> logger;
    QPushButton* startGame = nullptr;
    QPushButton* toSettings = nullptr;
    void resizeEvent(QResizeEvent* event) override;

signals:
    void switchToSettings();
    void switchToGame();
};

};


#endif // MENU_H