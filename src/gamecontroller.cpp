#include "gamecontroller.h"

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

    void GameController::startGame() {
        initBoard();
        food = std::make_shared<nFood::Food>(numberOfCellsLength, numberOfCellsWidth);
        snake = std::make_shared<nSnake::Snake>(numberOfCellsLength, numberOfCellsWidth);
        spawnFood();
        board->setFood(food);
        board->setSnake(snake);
        gameTimer->start();
        logger->info("GameController успешно начал игру");
    }

    std::shared_ptr<nGameView::GameView> GameController::getBoard(){
        return board;
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
        if (!emptyCells.empty()) {
            food->respawn(emptyCells);
            std::optional<QPoint> pos = food->getPosition();
            if (pos.has_value()) {
                QPoint valuePos = pos.value();
                gameBoard->setCell(valuePos.x(), valuePos.y(), nGameBoard::TypeCell::food);
                logger->info("Информация о создании еды в клетке успешно передана в GameBoard");
            } else {
                logger->error("Не удалось создать еду в GameController");
            }
        } else {
            // Игра завершилась
        }
    }

    void  GameController::update() {
        lastMoveTime = QDateTime::currentMSecsSinceEpoch();
        board->setLastMoveTime(lastMoveTime); // Устанавливаем, когда был последний запуск
        
        nSnake::Movement currentDirection = snake->getCurrentDirection();
        
        QPoint headPosition = snake->move();
        
        if (snake->checkCollusion()) {
            isGameOver = true;
            board->showGameOverScreen();
            emit gameOver();
            return;
        }

        const nGameBoard::Cell& positionWhereSnake = gameBoard->getCell(headPosition.x(),
        headPosition.y());
        if (positionWhereSnake.type == nGameBoard::TypeCell::food) { // Проверка, что змея съела еду
            snake->grow();
            const std::vector<QPoint>& freeCells = gameBoard->getEmptyCells();
            auto position = food->clear();
            if (position.has_value()) {
                gameBoard->setCell(position.value().x(), position.value().y(),
                nGameBoard::TypeCell::grass);
                food->respawn(freeCells);
                std::optional<QPoint> pos = food->getPosition();
                if (pos.has_value()) {
                    QPoint valuePos = pos.value();
                    gameBoard->setCell(valuePos.x(), valuePos.y(), nGameBoard::TypeCell::food);
                    logger->info("Информация о создании еды в клетке успешно передана в GameBoard");
                } else {
                    logger->error("Не удалось создать еду в GameController");
                }
            } else {

            }
        }
        
        board->update();
        logger->info("Пройдён update");
    }

    void GameController::changeDirection(nSnake::Movement newDirection) {
        snake->setDirection(newDirection);
    }

}; // nGameController