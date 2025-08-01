#include "gameboard.h"

namespace nGameBoard {
    GameBoard::GameBoard() {
        numberOfCellsLength = nSettings::Settings::getLength();
        numberOfCellsWidth = nSettings::Settings::getWidth();
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

    QPixmap GameBoard::loadTextureWithTurn(int turn, QPixmap baseImage) {
        return baseImage.transformed(QTransform().rotate(turn), Qt::SmoothTransformation);
    }

    void GameBoard::loadTextures() {        
        textures.insert(grass,
                loadTexture(QCoreApplication::applicationDirPath() + "/../images/grass.jpg"));

        textures.insert(food,
                loadTexture(QCoreApplication::applicationDirPath() + "/../images/apple.png"));
    }

    void GameBoard::createBoard() {
        board.resize(numberOfCellsWidth);
        for (int i = 0; i < numberOfCellsWidth; ++i) {
            board[i].resize(numberOfCellsLength);
            for (int j = 0; j < numberOfCellsLength; ++j) {
                Cell cell{i, j, grass};
                board[i][j] = cell;
            }
        }
        Cell cellHead{numberOfCellsWidth / 2, numberOfCellsLength / 2, TypeCell::snake};
        Cell cellTail{numberOfCellsWidth / 2 - 1, numberOfCellsLength / 2, TypeCell::snake};
        board[numberOfCellsWidth / 2][numberOfCellsLength / 2] = cellHead;
        board[numberOfCellsWidth / 2 - 1][numberOfCellsLength / 2] = cellTail;
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
        for (int i = 0; i < numberOfCellsWidth; ++i) {      // Цикл по ширине (X)
            for (int j = 0; j < numberOfCellsLength; ++j) {  // Цикл по высоте (Y)
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
}