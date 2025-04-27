#include "gameview.h"

namespace nGameBoard {

    GameBoard::GameBoard(QWidget* parent) {        
        logger = Log::Logger::getLogger();
        
        numberOfCellsLength = nSettings::Settings::getLength();
        numberOfCellsWidth = nSettings::Settings::getWidth();
    }

    void GameBoard::createBoard() {
        //QString fieldPath = QCoreApplication::applicationDirPath() 
        //+ "/../images/field1.jpg";
        board.resize(numberOfCellsWidth);
        for (int i = 0; i < numberOfCellsWidth; ++i) {
            board[i].resize(numberOfCellsLength);
            for (int j = 0; j < numberOfCellsLength; ++j) {
                Cell cell;
                QString fieldPath = "/home/paltsehvat/Документы/C++ development/Projects/Snake/images/field.jpg";
                if (!cell.texture.load(fieldPath)) {
                    logger->error("Не удалось загрузить клетку ({}, {}): {}",
                                   i, j, fieldPath.toStdString());
                } else {
                    logger->info("Клетка ({}, {}) загружена успешно", i, j);
                }
                cell.col = i;
                cell.row = j;
                board[i][j] = cell;
            }
        }
    }

    void GameBoard::drawBoard(QPainter& p) {
        for (int i = 0; i < numberOfCellsWidth; ++i) {
            for (int j = 0; j < numberOfCellsLength; ++j) {
                const Cell& cell = board[i][j];
                QRect rect(i * sizeCell, j * sizeCell, sizeCell, sizeCell);
                p.drawPixmap(rect, cell.texture);
            }
        }
    }

    void GameBoard::paintEvent(QPaintEvent*) {
        QPainter p(this);
        drawBoard(p);
        //food.draw(p, sizeCell);
        //snake.draw(p, sizeCell);
    }

    void GameBoard::resizeEvent(QResizeEvent* event) {
        int w = this->width();
        int h = this->height();

        sizeCell = std::min(w / numberOfCellsWidth, h / numberOfCellsLength);
        update();
    }

    QSize GameBoard::sizeHint() const {
        return QSize(400, 400);
    }
};