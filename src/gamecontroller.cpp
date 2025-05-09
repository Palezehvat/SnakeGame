#include "gamecontroller.h"

namespace nGameController {
    GameController::GameController(QObject* parent) {
        logger = Log::Logger::getLogger();
        
        numberOfCellsLength = nSettings::Settings::getLength();
        numberOfCellsWidth = nSettings::Settings::getWidth();
        sizeCell = nSettings::Settings::getSizeCell();
        logger->info("Класс GameController успешно инициализирован");
    }

    void GameController::startGame() {
        initBoard();
        food = std::make_shared<nFood::Food>(numberOfCellsLength, numberOfCellsWidth);
        //snake = new nSnake::Snake(board);
        spawnFood();
        board->setFood(food);
        //spawnSnake();
        logger->info("GameController успешно начал игру");
    }

    std::shared_ptr<nGameView::GameView> GameController::getBoard(){
        return board;
    }

    void GameController::initBoard() {
        gameBoard = std::make_shared<nGameBoard::GameBoard>();
        //logger->info("!");
        gameBoard->createBoard();
        board = std::make_unique<nGameView::GameView>(sizeCell, numberOfCellsLength, numberOfCellsWidth);
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
        // Здесь будет основная логика:
        // 1. Передвинуть змейку (snake->move())
        // 2. Проверить столкновения (со стенами, с собой)
        // 3. Проверить, съела ли змейка еду
        //    - Если да: snake->grow(), spawnFood(), увеличить счет
        // 4. Обновить отображение (gameView->update() или сигнал контроллера)
        logger->info("Пройдён update");
    }

}; // nGameController