#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <queue>
#include "settings.h"
#include "gameboard.h"
#include "food.h"
#include "snake.h"
#include "logger.h"
#include "gameview.h" 
#include "score.h"
#include "gamepanel.h"

namespace nGameView {
    class GameView;
}

namespace nGameController {
    
class GameController : public QObject {
    Q_OBJECT

public:
    explicit GameController(std::shared_ptr<nSettings::Settings> settings,
        QObject* parent = nullptr);
    std::shared_ptr<nGamePanel::GamePanel> startGame();
    void update();
    void restart();
    void setPause();
    void changeDirection(nSnake::Movement newDirection);
private:
    std::shared_ptr<nGameBoard::GameBoard> gameBoard = nullptr;
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::shared_ptr<nSnake::Snake> snake = nullptr;
    std::shared_ptr<nFood::Food> food = nullptr;
    std::shared_ptr<nGameView::GameView> board = nullptr;
    std::shared_ptr<nScore::Score> score = nullptr;
    std::shared_ptr<nGamePanel::GamePanel> panel = nullptr;
    std::shared_ptr<nSettings::Settings> settings = nullptr;
    std::shared_ptr<std::queue<nSnake::Movement>> moves = nullptr;

    unsigned int numberOfCellsInHeight;
    unsigned int numberOfCellsInWidth;

    qint64 lastMoveTime;
    int gameUpdateIntervalMs = 300;
    QTimer* gameTimer;
    bool isPause;
    bool isGameOver;

    void initBoard(unsigned int numberOfCellsInWidth,
                   unsigned int numberOfCellsInHeight);
    void spawnFood();
    void clearQueueOfMoves(std::shared_ptr<std::queue<nSnake::Movement>>& moves);               
signals:
    void gameOver();
}; // GameController

}; // nGameController

#endif // GAMECONTROLLER_H