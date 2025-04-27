#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QPainter>
#include "settings.h"
#include "logger.h"


namespace nGameBoard{

struct Cell {
    int row;
    int col;
    QPixmap texture;
};
    
class GameBoard : public QWidget {
public:
    GameBoard(QWidget* parent = nullptr);
    void createBoard();

private:
    int sizeCell = 20;
    int numberOfCellsLength;
    int numberOfCellsWidth;
    QVector<QVector<Cell>> board;
    std::shared_ptr<spdlog::logger> logger;

    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
    void drawBoard(QPainter& p);
    QSize sizeHint() const override;
};

}; // nGameBoard

#endif //GAMEVIEW_H