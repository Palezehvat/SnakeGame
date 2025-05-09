#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QPainter>
#include "settings.h"
#include "logger.h"
#include "gameboard.h"
#include "food.h"
#include "snake.h"


namespace nGameView{

class GameView : public QWidget {
public:
    GameView(int sizeCell, int length, int width, QWidget* parent = nullptr);
    void setGameBoard(std::shared_ptr<nGameBoard::GameBoard> board);
    void setFood(std::shared_ptr<nFood::Food>);
    //void setSnake(std::shared_ptr<nSnake::Snake);

private:
    int sizeCell;
    int numberOfCellsLength;
    int numberOfCellsWidth;
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<nGameBoard::GameBoard> gameboard;
    std::shared_ptr<nFood::Food> food;


    void paintEvent(QPaintEvent*) override;
    void resizeEvent(QResizeEvent* event) override;
    void drawBoard(QPainter& p);
    void drawFood(QPainter& p);
    QSize sizeHint() const override;
};

}; // nGameBoard

#endif //GAMEVIEW_H