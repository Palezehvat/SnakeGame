#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "gameboard.h"
#include "gameview.h"
#include "food.h"
#include "snake.h"
#include "logger.h"

namespace nGameController {
    
class GameController : public QObject {
public:
    explicit GameController(QObject* parent = nullptr);
    void startGame();
    void update();
    std::shared_ptr<nGameView::GameView> getBoard();
private:
    std::shared_ptr<nGameBoard::GameBoard> gameBoard = nullptr;
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<nGameView::GameView> board = nullptr;
    //std::shared_ptr<nSnake::Snake> snake = nullptr;
    std::shared_ptr<nFood::Food> food = nullptr;

    int sizeCell;
    int numberOfCellsLength;
    int numberOfCellsWidth;
    void initBoard();
    void spawnFood();
};

}; // nGameController

#endif // GAMECONTROLLER_H