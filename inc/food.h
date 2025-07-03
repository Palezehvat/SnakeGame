#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <QRandomGenerator>
#include "logger.h"


namespace nFood {

class Food {
public:
    Food(int length, int width);
    void respawn(const std::vector<QPoint>& freeCells);
    std::optional<QPoint> getPosition() const;
    std::optional<QPoint> clear();

private:
    std::shared_ptr<spdlog::logger> logger;
    int numberOfCellsLength;
    int numberOfCellsWidth;
    std::optional<QPoint> position;
};

}; // nFood

#endif // FOOD_H