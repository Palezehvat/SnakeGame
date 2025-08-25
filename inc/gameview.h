#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QPainter>
#include <QDateTime>
#include <QTimer>
#include <QKeyEvent>
#include <QPainterPath>
#include <QApplication>
#include <iostream>
#include "settings.h"
#include "logger.h"
#include "gameboard.h"
#include "food.h"
#include "snake.h"
#include "gamecontroller.h"
#include "uisettings.h"

namespace nGameController {
    class GameController;
}

namespace nGameView {

class GameView : public QWidget {
    Q_OBJECT

public:
    GameView(nGameController::GameController* controller, 
        int gameUpdateInterval, QWidget* parent = nullptr);
    void setGameBoard(std::shared_ptr<nGameBoard::GameBoard> board);
    void setFood(std::shared_ptr<nFood::Food> food);
    void setSnake(std::shared_ptr<nSnake::Snake> snake);
    void setLastMoveTime(qint64 lastMoveTime);
    int getPreferredWidth() const;
    int getPreferredHeight() const;
    void stopAnimation();
    void continueAnimation();
    void restart();

private:
    QColor colorEvenField;
    QColor colorOddField;
    QColor colorBackground;
    qreal headRenderAngle = 0.0;
    bool headAngleInitialized = false;
    qreal sizeCell;
    bool animationFrozen;
    qreal pausedT;
    unsigned int maximumNumberOfCellsInHeight;
    unsigned int maximumNumberOfCellsInWidth;
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<nGameBoard::GameBoard> gameboard;
    std::shared_ptr<nFood::Food> food;
    std::shared_ptr<nSnake::Snake> snake;
    nGameController::GameController* controller;
    QTimer* frameTimer = nullptr;
    qint64 lastMoveTime = 0;
    int gameUpdateIntervalMs;

    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
    void drawBoard(QPainter& p);
    void drawApple(QPainter& p, QPointF center);
    void drawFood(QPainter& p);
    void drawSnake(QPainter& p);
    void drawEyes(QPainter& p, QPointF p1, QPointF p2);
    void drawRotatedHead(QPainter& p, QPointF center, qreal angle);
    void keyPressEvent(QKeyEvent* event);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const;
};

}; // nGameBoard

#endif //GAMEVIEW_H