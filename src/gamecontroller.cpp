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

    std::shared_ptr<nGamePanel::GamePanel> GameController::startGame() {
        initBoard();
        score = std::make_shared<nScore::Score>();
        food = std::make_shared<nFood::Food>(numberOfCellsLength, numberOfCellsWidth);
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
            // Тут обработать победу в игре, когда вся карта заполнена
        }
    }

    void GameController::update() {
        lastMoveTime = QDateTime::currentMSecsSinceEpoch();
        board->setLastMoveTime(lastMoveTime);
        
        QPoint headPosition = snake->move();
        
        if (snake->checkCollusion()) {
            isGameOver = true;
            panel->showGameOverScreen();
            emit gameOver();
            return;
        }
    
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

}; // nGameController