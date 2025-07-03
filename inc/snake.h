#ifndef SNAKE_H
#define SNAKE_H


#include <vector>
#include <QPoint>
#include <optional>
#include "logger.h"


namespace nSnake {

enum Movement {
    Right,
    Left,
    Up,
    Down
};
    
class Snake {
public:
    Snake(int length, int width);
    QPoint move();
    void setDirection(Movement newDirection);
    void grow();
    bool checkCollusion() const;
    const std::vector<QPoint> getBody() const;
    const std::vector<QPoint> getPrevBody() const;
    std::vector<QPointF> getInterpolatedBody(qreal t);
    const Movement getCurrentDirection() const;
    const Movement getPreviousDirection() const;

private:
    bool checkCollusionWalls() const;
    bool checkCollusionBody() const;

    std::shared_ptr<spdlog::logger> logger;
    
    Movement previousDirection;
    Movement currentDirection;
    Movement nextDirection;
    
    int numberOfCellsLength;
    int numberOfCellsWidth;
    
    int growPending = 0;

    std::vector<QPoint> prevBody;
    std::vector<QPoint> currBody;
}; // Snake

} // nSnake

#endif // SNAKE_H