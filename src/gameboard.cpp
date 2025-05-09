#include "gameboard.h"

namespace nGameBoard {
    GameBoard::GameBoard() {
        this->numberOfCellsLength = nSettings::Settings::getLength();
        this->numberOfCellsWidth = nSettings::Settings::getWidth();
        logger = Log::Logger::getLogger();
        loadTextures();
        logger->info("Класс GameBoard успешно инициализирован");
    }

    void GameBoard::loadTextures() {
        QPixmap grassPixmap;
        QString grassPath = QCoreApplication::applicationDirPath() + "/../images/grass.jpg";
        if (!grassPixmap.load(grassPath)) {
            logger->error(fmt::format("Не удалось загрузить текстуру поля: {}",
                                           grassPath.toStdString()));
        } else {
            logger->info(fmt::format("Текстура поля успешно загружена: {}",
                                           grassPath.toStdString()));
        }
        
        textures.insert(grass, grassPixmap);

        QPixmap foodPixmap;
        QString foodPath = QCoreApplication::applicationDirPath() + "/../images/apple.png";
        if (!foodPixmap.load(foodPath)) {
            logger->error(fmt::format("Не удалось загрузить текстуру поля: {}",
                                           foodPath.toStdString()));
        } else {
            logger->info(fmt::format("Текстура поля успешно загружена: {}",
                                           foodPath.toStdString()));
        }
        
        textures.insert(food, foodPixmap);
        // Тут могут быть другие текстуры, пока, что без них
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
        for (int i = 0; i < numberOfCellsLength; ++i) {
            for (int j = 0; j < numberOfCellsWidth; ++j) {
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