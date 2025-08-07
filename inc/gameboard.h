#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPixmap>
#include <QWidget>
#include <QCoreApplication>
#include "logger.h"
#include "settings.h"
#include "uisettings.h"

namespace nGameBoard{

enum TypeCell {
    grass,
    food,
    snake,
    rock
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
    void createBoard(unsigned int numberOfCellsInWidth, unsigned int numberOfCellsInHeight);
    std::vector<QPoint> getEmptyCells() const;
    void restart(int width, int height);

private:
    void loadTextures();
    QPixmap loadTexture(QString path);
    QMap<TypeCell, QPixmap> textures;
    std::shared_ptr<spdlog::logger> logger;
    QVector<QVector<Cell>> board;

    unsigned int maximumNumberOfCellsInHeight;
    unsigned int maximumNumberOfCellsInWidth;

    unsigned int numberOfCellsInHeight;
    unsigned int numberOfCellsInWidth;
};

};

#endif // GAMEBOARD_H