#include "gamecontroller.h"

namespace nGameController {
    GameController::GameController(std::shared_ptr<nSettings::Settings> settings,
        QObject* parent) {
        logger = Log::Logger::getLogger();
        this->settings = settings;
        
        numberOfCellsInHeight = settings->getHeight();
        numberOfCellsInWidth = settings->getWidth();

        gameTimer = new QTimer(this);
        connect(gameTimer, &QTimer::timeout, this, &GameController::update);
        gameTimer->setInterval(gameUpdateIntervalMs);
        score = std::make_shared<nScore::Score>();
        connect(score.get(), &nScore::Score::pause, this, &GameController::setPause);
        logger->info("Класс GameController успешно инициализирован");
        isPause = false;
        isGameOver = false;
    }

    std::shared_ptr<nGamePanel::GamePanel> GameController::startGame() {
        numberOfCellsInHeight = settings->getHeight();
        numberOfCellsInWidth = settings->getWidth();
        initBoard(numberOfCellsInWidth, numberOfCellsInHeight);
        food = std::make_shared<nFood::Food>();
        snake = std::make_shared<nSnake::Snake>(numberOfCellsInWidth, numberOfCellsInHeight);
        spawnFood();
        board->setFood(food);
        board->setSnake(snake);
        panel = std::make_shared<nGamePanel::GamePanel>(board, score);
        connect(panel.get(), &nGamePanel::GamePanel::gameOver, this, [=](){
            isGameOver = true;
        });
        gameTimer->start();
        logger->info("GameController успешно начал игру");
        return panel;
    }

    void GameController::initBoard(unsigned int numberOfCellsInWidth,
                                   unsigned int numberOfCellsInHeight) {
        gameBoard = std::make_shared<nGameBoard::GameBoard>();
        gameBoard->createBoard(numberOfCellsInWidth, numberOfCellsInHeight);
        board = std::make_unique<nGameView::GameView>(this, gameUpdateIntervalMs,
                        numberOfCellsInHeight, numberOfCellsInWidth, settings->getKeys());
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

    void GameController::setPause() {
        if (isGameOver) return;
        isPause = !isPause;
        if (isPause) {
            gameTimer->stop();
            qint64 startPause = QDateTime::currentMSecsSinceEpoch();
            board->stopAnimation();
        } else {
            board->continueAnimation();
            gameTimer->start();
        }
    }

    void GameController::update() {
        QPoint headPositionAfterMove = snake->getNextHeadPosition();

        bool collusion = false;

        if (headPositionAfterMove.x() < 0 || headPositionAfterMove.x() >= numberOfCellsInWidth ||
            headPositionAfterMove.y() < 0 || headPositionAfterMove.y() >= numberOfCellsInHeight) {
            collusion = true; // Вышла за пределы поля
        } else {
            const std::vector<QPoint> currBody = snake->getBody();
            for(auto partSnake : currBody) {
                if (partSnake == headPositionAfterMove && headPositionAfterMove != currBody[0]) {
                    collusion = true; // Врезалась в себя
                }
            }
        }
        
        if (collusion || isGameOver) {
            score->showGameOverScreen();
            gameTimer->stop();
            emit gameOver();
            board->stopAnimation();
            isGameOver = true;
            return;
        }
        
        lastMoveTime = QDateTime::currentMSecsSinceEpoch();
        board->setLastMoveTime(lastMoveTime);

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
        if (isGameOver) return;
        snake->setDirection(newDirection);
    }

    void GameController::restart() {
        isPause = false;
        isGameOver = false;
        numberOfCellsInHeight = settings->getHeight();
        numberOfCellsInWidth = settings->getWidth();

        gameTimer->stop();

        gameBoard->restart(numberOfCellsInWidth, numberOfCellsInHeight);
        snake->restart(numberOfCellsInWidth, numberOfCellsInHeight);
        food->restart();
        spawnFood();

        score->restart();
        board->restart(numberOfCellsInHeight, numberOfCellsInWidth);

        if (gameTimer->isActive()) {
            gameTimer->stop();
        }

        gameTimer->setInterval(gameUpdateIntervalMs);
        gameTimer->start();
    }

}; // nGameController