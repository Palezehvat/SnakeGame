/**
 * @file food.h
 * @brief Логика, связанная с едой 
 */

#ifndef FOOD_H
#define FOOD_H

#include <QPoint>
#include <QRandomGenerator>
#include "logger.h"

/**
 * @namespace nFood
 * @brief Содержит в себе класс Food
 */
namespace nFood {

/**
 * @class Food
 * @brief Класс для создания еды в свободных клетках
 */
class Food {
public:
    /// Конструктор
    Food();
    /**
     * @brief Определяет случайным образом новую позицию для еды
     * @param freeCells Свободные клетки под еду
     */
    void respawn(const std::vector<QPoint>& freeCells);
    /**
     * @brief Получение позиции, где должна находиться еда
     * @return QPoint, если существует позиция, которую занимает еда, иначе nullopt
     */
    std::optional<QPoint> getPosition() const;
    /**
     * @brief Очистка позиции, которую занимает еда
     * @return QPoint если такая позиция существовала, иначе nullopt
     */
    std::optional<QPoint> clear();

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::optional<QPoint> position = std::nullopt;
};

}; // nFood

#endif // FOOD_H