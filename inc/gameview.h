#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QPainter>
#include <QDateTime>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include "settings.h"
#include "logger.h"
#include "gameboard.h"
#include "food.h"
#include "snake.h"
#include "gamecontroller.h"

namespace nGameController {
    class GameController;
}

namespace nGameView{

class GameView : public QWidget {
    Q_OBJECT

public:
    GameView(nGameController::GameController* controller, 
        int length, int width, int gameUpdateInterval, QWidget* parent = nullptr);
    void setGameBoard(std::shared_ptr<nGameBoard::GameBoard> board);
    void setFood(std::shared_ptr<nFood::Food> food);
    void setSnake(std::shared_ptr<nSnake::Snake> snake);
    void setLastMoveTime(qint64 lastMoveTime);
    void showGameOverScreen();

private:
    int sizeCell;
    int numberOfCellsLength;
    int numberOfCellsWidth;
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<nGameBoard::GameBoard> gameboard;
    std::shared_ptr<nFood::Food> food;
    std::shared_ptr<nSnake::Snake> snake;
    nGameController::GameController* controller;
    QPushButton* restartButton = nullptr;
    QPushButton* menuButton = nullptr;
    QTimer* frameTimer = nullptr;
    qint64 lastMoveTime = 0;
    int gameUpdateIntervalForAnimation;

    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
    void drawBoard(QPainter& p);
    void drawFood(QPainter& p);
    void drawSnake(QPainter& p);
    void keyPressEvent(QKeyEvent* event);
    QSize sizeHint() const override;

signals:
    void backToMenu();
    void restartGame(); // Реализовать
};

}; // nGameBoard

#endif //GAMEVIEW_H