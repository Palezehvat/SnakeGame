#include "snake.h"

namespace nSnake {
    Snake::Snake(int length, int width) : numberOfCellsWidth(width), numberOfCellsLength(length) {
        logger = Log::Logger::getLogger();
        currentDirection = Right;
        nextDirection = Right;
    
        QPoint headPosition = {width / 2, length / 2};
        QPoint tailPosition = {width / 2 - 1, length / 2};
    
        currBody.push_back(tailPosition);
        currBody.push_back(headPosition);
    
        prevBody = currBody;
    
        logger->info("Инициализация змеи прошла успешно");
    }

    QPoint partMove(QPoint position, Movement move) {
        switch (move) {
            case Left:  return {position.x() - 1, position.y()};
            case Right: return {position.x() + 1, position.y()};
            case Up:    return {position.x(), position.y() - 1};
            case Down:  return {position.x(), position.y() + 1};
        }
        return position;
    }

    std::string stringFormatMovement(Movement move) {
        switch (move) {
            case Left:  return "Left";
            case Right: return "Right";
            case Up:    return "Up";
            case Down:  return "Down";
        }
        return "Unknown";
    }

    QPoint Snake::move() {
        previousDirection = currentDirection;
        currentDirection = nextDirection;
        prevBody = currBody;
        std::optional<QPoint> removeTailPos = std::nullopt;
        QPoint newHead = partMove(currBody.back(), currentDirection);
        currBody.push_back(newHead);
        if (growPending > 0) {
            --growPending;
        } else {
            currBody.erase(currBody.begin());
        }
        logger->info(fmt::format("Змея сделала движение в направлении: {}",
            stringFormatMovement(currentDirection)));
        return currBody[currBody.size() - 1];
    }

    void Snake::setDirection(Movement newDirection) {
        if (currentDirection == Left && newDirection == Right ||
            currentDirection == Right && newDirection == Left ||
            currentDirection == Up && newDirection == Down ||
            currentDirection == Down && newDirection == Up) {
            return;
        }
        nextDirection = newDirection; 
    }
    
    void Snake::grow() {
        ++growPending;
        logger->info("Змейке добавлен сегмент для роста");
    }

    bool Snake::checkCollusionWalls() const {
        const QPoint& head = currBody.back();
        return head.x() < 0 || head.x() >= numberOfCellsWidth ||
               head.y() < 0 || head.y() >= numberOfCellsLength;
    }

    bool Snake::checkCollusionBody() const {
        const QPoint& head = currBody.back();
        for (size_t i = 0; i + 1 < currBody.size(); ++i) {
            if (currBody[i] == head) return true;
        }
        return false;
    }

    bool Snake::checkCollusion() const {
        return Snake::checkCollusionWalls() || Snake::checkCollusionBody();
    }

    const std::vector<QPoint> Snake::getBody() const {
        return currBody;
    }

    const std::vector<QPoint> Snake::getPrevBody() const {
        return prevBody;
    }

    std::vector<QPointF> Snake::getInterpolatedBody(qreal t) {
        std::vector<QPointF> result;
        
        if (currBody.size() != prevBody.size()) {
            for (const auto& segment : currBody) {
                result.push_back(QPointF(segment));
            }
            return result;
        }
    
        for (size_t i = 0; i < currBody.size(); ++i) {
            QPointF start = prevBody[i];
            QPointF end = currBody[i];
            QPointF interpolated = start * (1.0 - t) + end * t;
            result.push_back(interpolated);
        }
        return result;
    }

    const Movement Snake::getCurrentDirection() const {
        return currentDirection;
    }

    const Movement Snake::getPreviousDirection() const {
        return previousDirection;
    }
} // nSnake