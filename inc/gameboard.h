#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPixmap>
#include <QWidget>
#include "logger.h"
#include "settings.h"

namespace nGameBoard{

enum TypeCell {
    grass,
    snake,
    food
};

struct Cell {
    int row;
    int col;
    TypeCell type;
};
    
class GameBoard {
public:
    GameBoard();
    const Cell& getCell(int x, int y) const;
    void setCell(int x, int y, TypeCell type);
    const QMap<TypeCell, QPixmap>& getTextures();
    void createBoard();
    std::vector<QPoint> getEmptyCells() const;

private:
    void loadTextures();
    QMap<TypeCell, QPixmap> textures;
    std::shared_ptr<spdlog::logger> logger;
    QVector<QVector<Cell>> board;
    int numberOfCellsLength;
    int numberOfCellsWidth;
};

};

#endif // GAMEBOARD_H