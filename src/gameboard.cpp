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
        
        QPixmap bodyVertical = loadTexture(QCoreApplication::applicationDirPath()
                            + "/../images/snake/snake-body-vertical.png");
        textures.insert(TypeCell::bodyVertical, bodyVertical);
        textures.insert(TypeCell::bodyHorizontal, loadTextureWithTurn(90, bodyVertical));
        
        QPixmap bodyRight = loadTexture(QCoreApplication::applicationDirPath()
                            + "/../images/snake/snake-body-angle-right.png");
        textures.insert(TypeCell::bodyRight, bodyRight);
        textures.insert(TypeCell::bodyDown, loadTextureWithTurn(90, bodyRight));
        textures.insert(TypeCell::bodyLeft, loadTextureWithTurn(180, bodyRight));
        textures.insert(TypeCell::bodyUp, loadTextureWithTurn(270, bodyRight));

        QPixmap headUp = loadTexture(QCoreApplication::applicationDirPath()
                            + "/../images/snake/snake-head-up.png");
        textures.insert(TypeCell::headUp, headUp);
        textures.insert(TypeCell::headLeft, loadTextureWithTurn(90, headUp));
        textures.insert(TypeCell::headDown, loadTextureWithTurn(180, headUp));
        textures.insert(TypeCell::headRight, loadTextureWithTurn(270, headUp));

        QPixmap headTurnRight = loadTexture(QCoreApplication::applicationDirPath()
                            + "/../images/snake/snake-head-angle-right.png");
        textures.insert(TypeCell::headTurnRight, headTurnRight);
        textures.insert(TypeCell::headTurnUp, loadTextureWithTurn(90, headTurnRight));
        textures.insert(TypeCell::headTurnLeft, loadTextureWithTurn(180, headTurnRight));
        textures.insert(TypeCell::headTurnDown, loadTextureWithTurn(270, headTurnRight));

        QPixmap tailUp = loadTexture(QCoreApplication::applicationDirPath()
                            + "/../images/snake/snake-tail-up.png");
        textures.insert(TypeCell::tailUp, tailUp);
        textures.insert(TypeCell::tailLeft, loadTextureWithTurn(90, tailUp));
        textures.insert(TypeCell::tailDown, loadTextureWithTurn(180, tailUp));
        textures.insert(TypeCell::tailRight, loadTextureWithTurn(270, tailUp));

        QPixmap tailTurnRight = loadTexture(QCoreApplication::applicationDirPath()
                            + "/../images/snake/snake-tail-angle-right.png");
        textures.insert(TypeCell::tailTurnRight, tailTurnRight);
        textures.insert(TypeCell::tailTurnUp, loadTextureWithTurn(90, tailTurnRight));
        textures.insert(TypeCell::tailTurnLeft, loadTextureWithTurn(180, tailTurnRight));
        textures.insert(TypeCell::tailTurnDown, loadTextureWithTurn(270, tailTurnRight));
        
        // Инвертировать голову и хвост(повороты)
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
        Cell cellHead{numberOfCellsWidth / 2, numberOfCellsLength / 2, TypeCell::headRight};
        Cell cellTail{numberOfCellsWidth / 2 - 1, numberOfCellsLength / 2, TypeCell::tailLeft};
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