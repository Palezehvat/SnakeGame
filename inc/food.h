#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <QRandomGenerator>
#include "logger.h"


namespace nFood {

class Food {
public:
    Food();
    void respawn(const std::vector<QPoint>& freeCells);
    std::optional<QPoint> getPosition() const;
    std::optional<QPoint> clear();
    void restart();

private:
    std::shared_ptr<spdlog::logger> logger;
    std::optional<QPoint> position;
};

}; // nFood

#endif // FOOD_H