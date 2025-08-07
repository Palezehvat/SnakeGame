#include "gameboard.h"
#include <iostream>

namespace nGameBoard {
    GameBoard::GameBoard() {
        maximumNumberOfCellsInHeight = UISettings::maxHeight;
        maximumNumberOfCellsInWidth = UISettings::maxWidth;
        logger = Log::Logger::getLogger();
        loadTextures();
        logger->info("Класс GameBoard успешно инициализирован");
    }

    QPixmap GameBoard::loadTexture(QString path) {
        QPixmap image;
        if (!image.load(path)) {
            logger->error(fmt::format("Не удалось загрузить текстуру поля: {}",
                                           path.toStdString()));
        } else {
            logger->info(fmt::format("Текстура поля успешно загружена: {}",
                                           path.toStdString()));
        }
        return image;
    }

    void GameBoard::loadTextures() {        
        textures.insert(grass,
                loadTexture(QCoreApplication::applicationDirPath() + "/../images/grass.jpg"));

        textures.insert(food,
                loadTexture(QCoreApplication::applicationDirPath() + "/../images/apple.png"));

        textures.insert(rock,
                loadTexture(QCoreApplication::applicationDirPath() + "/../images/rock.png"));
    }

    void GameBoard::createBoard(unsigned int numberOfCellsInWidth,
                                unsigned int numberOfCellsInHeight) {
        
        this->numberOfCellsInWidth = numberOfCellsInWidth;
        this->numberOfCellsInHeight = numberOfCellsInHeight;
        
        board.resize(maximumNumberOfCellsInWidth);
        for (int i = 0; i < maximumNumberOfCellsInWidth; ++i) {
            board[i].resize(maximumNumberOfCellsInHeight);
            for (int j = 0; j < maximumNumberOfCellsInHeight; ++j) {
                Cell cell;
                if (i >= numberOfCellsInWidth || j >= numberOfCellsInHeight) {
                    cell = Cell{i, j, rock};
                } else {
                    cell = Cell{i, j, grass};
                }
                board[i][j] = cell;
            }
        }

        Cell cellHead{1, 0, TypeCell::snake};
        Cell cellTail{0, 0, TypeCell::snake};
        
        board[1][0] = cellHead;
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

    const QMap<TypeCell, QPixmap>& GameBoard::getTextures() {
        return textures;
    }

    void GameBoard::restart(int width, int height) {
        numberOfCellsInHeight = height;
        numberOfCellsInWidth = width;
        createBoard(numberOfCellsInWidth, numberOfCellsInHeight);
    }
}