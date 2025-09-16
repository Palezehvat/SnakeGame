#include "gameboard.h"

namespace nGameBoard {
    GameBoard::GameBoard() {
        logger = nLogger::Logger::getLogger();
        logger->info("Класс GameBoard успешно инициализирован");
    }

    void GameBoard::createBoard(unsigned int numberOfCellsInWidth,
                                unsigned int numberOfCellsInHeight) {
        
        this->numberOfCellsInWidth = numberOfCellsInWidth;
        this->numberOfCellsInHeight = numberOfCellsInHeight;
        
        board.resize(numberOfCellsInWidth);
        for (int i = 0; i < numberOfCellsInWidth; ++i) {
            board[i].resize(numberOfCellsInHeight);
            for (int j = 0; j < numberOfCellsInHeight; ++j) {
                Cell cell;
                cell = Cell{i, j, TypeCell::grass};
                board[i][j] = cell;
            }
        }

        Cell cellHead{2, 0, TypeCell::snake};
        Cell cellBody{1, 0, TypeCell::snake};
        Cell cellTail{0, 0, TypeCell::snake};
        
        board[2][0] = cellHead;
        board[1][0] = cellBody;
        board[0][0] = cellTail;
        logger->info("Доска для игры успешно создана"); 
    }

    const Cell& GameBoard::getCell(int x, int y) const {
        return board[x][y];
    }

    void GameBoard::setCell(int x, int y, TypeCell type) {
        board[x][y].type = type;
    }

    std::vector<QPoint> GameBoard::getEmptyCells() const {
        std::vector<QPoint> result;
        for (int i = 0; i < numberOfCellsInWidth; ++i) {      // Цикл по ширине (X)
            for (int j = 0; j < numberOfCellsInHeight; ++j) {  // Цикл по высоте (Y)
                if (board[i][j].type == TypeCell::grass) {
                    result.emplace_back(i, j);
                }
            }
        }
        return result;
    }

    void GameBoard::restart(int width, int height) {
        numberOfCellsInHeight = height;
        numberOfCellsInWidth = width;
        createBoard(numberOfCellsInWidth, numberOfCellsInHeight);
    }
}