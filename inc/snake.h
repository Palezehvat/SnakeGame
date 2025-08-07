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
    Snake(unsigned int width, unsigned int height);
    QPoint move();
    void setDirection(Movement newDirection);
    void grow();
    bool checkCollusion() const;
    const std::vector<QPoint> getBody() const;
    const std::vector<QPoint> getPrevBody() const;
    std::vector<QPointF> getInterpolatedBody(qreal t);
    const Movement getCurrentDirection() const;
    QPoint getNextHeadPosition() const;
    void restart(unsigned int width, unsigned int height);

private:
    bool checkCollusionWalls() const;
    bool checkCollusionBody() const;

    std::shared_ptr<spdlog::logger> logger;
    
    Movement currentDirection;
    Movement nextDirection;
    
    unsigned int numberOfCellsHeight;
    unsigned int numberOfCellsWidth;
    
    unsigned int growPending = 0;

    std::vector<QPoint> prevBody;
    std::vector<QPoint> currBody;
}; // Snake

} // nSnake

#endif // SNAKE_H