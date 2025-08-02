#include "gamecontroller.h"
#include <iostream>

namespace nGameController {
    GameController::GameController(QObject* parent) {
        logger = Log::Logger::getLogger();
        
        numberOfCellsLength = nSettings::Settings::getLength();
        numberOfCellsWidth = nSettings::Settings::getWidth();
        gameTimer = new QTimer(this);
        connect(gameTimer, &QTimer::timeout, this, &GameController::update);
        gameTimer->setInterval(gameUpdateIntervalMs);
        logger->info("Класс GameController успешно инициализирован");
    }

    std::shared_ptr<nGamePanel::GamePanel> GameController::startGame() {
        initBoard();
        score = std::make_shared<nScore::Score>();
        food = std::make_shared<nFood::Food>();
        snake = std::make_shared<nSnake::Snake>(numberOfCellsLength, numberOfCellsWidth);
        spawnFood();
        board->setFood(food);
        board->setSnake(snake);
        gameTimer->start();
        logger->info("GameController успешно начал игру");
        panel = std::make_shared<nGamePanel::GamePanel>(board, score);
        return panel;
    }

    void GameController::initBoard() {
        gameBoard = std::make_shared<nGameBoard::GameBoard>();
        gameBoard->createBoard();
        board = std::make_unique<nGameView::GameView>(this,
            numberOfCellsLength, numberOfCellsWidth, gameUpdateIntervalMs);
        board->setGameBoard(gameBoard);
    }

    void GameController::spawnFood() {
        std::vector<QPoint> emptyCells = gameBoard->getEmptyCells();
        
        const auto& snakeBody = snake->getBody();
        
        std::vector<QPoint> trulyEmptyCells;
        std::copy_if(emptyCells.begin(), emptyCells.end(), std::back_inserter(trulyEmptyCells),
            [&snakeBody](const QPoint& cell) {
                // Копируем клетку, только если она не найдена в теле змеи
                return std::find(snakeBody.begin(), snakeBody.end(), cell) == snakeBody.end();
            });

        if (!trulyEmptyCells.empty()) {
            food->respawn(trulyEmptyCells);
            std::optional<QPoint> pos = food->getPosition();
            if (pos.has_value()) {
                QPoint valuePos = pos.value();
                gameBoard->setCell(valuePos.x(), valuePos.y(), nGameBoard::TypeCell::food);
                logger->info("Информация о создании еды в клетке успешно передана в GameBoard");
            } else {
                logger->error("Не удалось создать еду в GameController");
            }
        } else {
            gameTimer->stop();
        }
    }

    void GameController::update() {
        lastMoveTime = QDateTime::currentMSecsSinceEpoch();
        board->setLastMoveTime(lastMoveTime);
        
        QPoint headPositionAfterMove = snake->getNextHeadPosition();

        bool collusion = false;

        if (headPositionAfterMove.x() < 0 || headPositionAfterMove.x() >= numberOfCellsWidth ||
            headPositionAfterMove.y() < 0 || headPositionAfterMove.y() >= numberOfCellsLength) {
            collusion = true; // Вышла за пределы поля
        } else {
            const std::vector<QPoint> currBody = snake->getBody();
            for(auto partSnake : currBody) {
                if (partSnake == headPositionAfterMove && headPositionAfterMove != currBody[0]) {
                    collusion = true; // Врезалась в себя
                }
            }
        }
        
        if (collusion) {
            panel->showGameOverScreen();
            gameTimer->stop();
            emit gameOver();
            board->stopAnimation();
            return;
        }
        
        QPoint headPosition = snake->move();
        
        const nGameBoard::Cell& positionWhereSnake = gameBoard->getCell(headPosition.x(),
         headPosition.y());
        
         if (positionWhereSnake.type == nGameBoard::TypeCell::food) {
            score->updateCounter();
            gameBoard->setCell(headPosition.x(), headPosition.y(), nGameBoard::TypeCell::grass);
            snake->grow();
            spawnFood();
        }
        
        board->update();
    }

    void GameController::changeDirection(nSnake::Movement newDirection) {
        snake->setDirection(newDirection);
    }

    void GameController::restart(int width, int length) {
        if (width != 0 && length != 0) {
            numberOfCellsLength = length;
            numberOfCellsWidth = width;
        }

        gameTimer->stop();

        gameBoard->restart(numberOfCellsWidth, numberOfCellsLength);
        snake->restart(numberOfCellsWidth, numberOfCellsLength);
        food->restart();
        spawnFood();

        panel->restart();
        score->restart();
        board->restart(numberOfCellsWidth, numberOfCellsLength);


        if (gameTimer->isActive()) {
            gameTimer->stop();
        }

        gameTimer->setInterval(gameUpdateIntervalMs);
        gameTimer->start();
    }

}; // nGameController