#include "gamecontroller.h"

namespace nGameController {
    GameController::GameController(std::shared_ptr<nSettings::Settings> settings,
        QObject* parent) {
        logger = nLogger::Logger::getLogger();
        this->settings = settings;

        numberOfCellsInHeight = settings->getHeight();
        numberOfCellsInWidth = settings->getWidth();
        moves = std::make_shared<std::queue<nSnake::Movement>>();

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
        currBodySnake = snake->getBody();
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
                        numberOfCellsInHeight, numberOfCellsInWidth, settings->getKeys(), moves);
        board->setGameBoard(gameBoard);
    }

    void GameController::spawnFood() {
        std::vector<QPoint> emptyCells = gameBoard->getEmptyCells();
        
        std::vector<QPoint> trulyEmptyCells;
        std::copy_if(emptyCells.begin(), emptyCells.end(), std::back_inserter(trulyEmptyCells),
            [=](const QPoint& cell) {
                // Копируем клетку, только если она не найдена в теле змеи
                return std::find(currBodySnake->begin(), currBodySnake->end(), cell) == currBodySnake->end();
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
        if (!moves->empty()) {
            changeDirection(moves->front());
            moves->pop();
        }

        QPoint headPositionAfterMove = snake->getNextHeadPosition();

        bool collusion = false;

        if (headPositionAfterMove.x() < 0 || headPositionAfterMove.x() >= numberOfCellsInWidth ||
            headPositionAfterMove.y() < 0 || headPositionAfterMove.y() >= numberOfCellsInHeight) {
            collusion = true; // Вышла за пределы поля
        } else {
            for(auto partSnake : (*currBodySnake)) {
                if (partSnake == headPositionAfterMove && headPositionAfterMove != (*currBodySnake)[0]) {
                    collusion = true; // Врезалась в себя
                }
            }
        }
        
        if (collusion || isGameOver) {
            gameTimer->stop();
            emit gameOver();
            isGameOver = true;

            qreal collisionT = board->computeCollision(currBodySnake->back(),
                                                    snake->getCurrentDirection());
            board->setCollision(collisionT);

            lastMoveTime = QDateTime::currentMSecsSinceEpoch();
            board->setLastMoveTime(lastMoveTime);
            snake->move();

            QTimer::singleShot(300, [this]() {
                board->stopAnimation();
            });
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
        snake->setNextDirection(newDirection);
    }

    void GameController::clearQueueOfMoves(std::shared_ptr<std::queue<nSnake::Movement>>& moves) {
        std::queue<nSnake::Movement> empty;
        std::swap((*moves), empty );
    }

    void GameController::restart() {
        isPause = false;
        isGameOver = false;
        clearQueueOfMoves(moves);
        numberOfCellsInHeight = settings->getHeight();
        numberOfCellsInWidth = settings->getWidth();

        gameTimer->stop();

        gameBoard->restart(numberOfCellsInWidth, numberOfCellsInHeight);
        snake->restart(numberOfCellsInWidth, numberOfCellsInHeight);
        food->clear();
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