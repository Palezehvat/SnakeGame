/**
 * @file snake.h
 * @brief Логика, связанная со змеёй
 */

#ifndef SNAKE_H
#define SNAKE_H


#include <vector>
#include <QPoint>
#include <optional>
#include "logger.h"

/**
 * @namespace nSnake
 * @brief Содержит в себе класс Snake, перечисление Movement
 */
namespace nSnake {

/**
 * @enum Movement
 * @brief Перечисление для указания типов возможных движений змеёй
 * 
 * Используется для различения разных типов движение:
 * - влево
 * - вправо
 * - вниз
 * - вверх
 */
enum Movement {
    Right,
    Left,
    Up,
    Down
};

/**
 * @class Snake
 * @brief Класс, ответственный за логику змеи
 */
class Snake {
public:
    /**
     * @brief Конструктор
     * @param width Ширина доски(количество клеток)
     * @param height Высота доски(количество клеток)
     */
    Snake(unsigned int width, unsigned int height);
    /**
     * @brief Змея делает движение на одну клетку
     * @return Новую позицию головы
     * Направление движения определяется в контроллере(nGameController::GameController)
     * @see nGameController::GameController
     */
    QPoint move();
    /// Установка направления движения змеи на следующий ход
    void setNextDirection(Movement newDirection);
    /// Указание змее, что она должна вырасти на один сегмент
    void grow();
    /**
     * @brief Проверка, на то что змея врезалась в стены или в себя
     * @return Истина, если змея врезалась, иначе ложь
     */
    bool checkCollusion() const;
    /// Получение указателя на занятые клеток змеёй
    std::shared_ptr<std::vector<QPoint>> getBody() const;
    /**
     * @brief Выполняет интерполяцию тела змеи между двумя состояниями
     * @param t Нормализованный параметр интерполяции в диапазоне [0, 1],
     *          где 0 соответствует положению до движения, а 1 — положению после движения
     * @return Вектор точек (QPointF), описывающий интерполированное положение сегментов змеи
     */
    std::vector<QPointF> getInterpolatedBody(qreal t);
    /// Возвращает текущее направление движения змеи
    const Movement getCurrentDirection() const;
    /// Получение позиции головы змеи и при текущем направлении движения змеи
    QPoint getNextHeadPosition() const;
    /**
     * @brief Перезапуск логики змеи
     * @param width Ширина поля(количество клеток)
     * @param height Высота поля(количество клеток)
     */
    void restart(unsigned int width, unsigned int height);

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    unsigned int numberOfCellsHeight = 0;
    unsigned int numberOfCellsWidth = 0;
    unsigned int growPending = 0;
    Movement currentDirection;
    Movement nextDirection;
    std::shared_ptr<std::vector<QPoint>> prevBody;
    std::shared_ptr<std::vector<QPoint>> currBody;
    
    /// Проверка на то, что змея врезалась в стены
    bool checkCollusionWalls() const;
    /// Проверка на то, что змея врезалась в себя
    bool checkCollusionBody() const;
}; // Snake

} // nSnake

#endif // SNAKE_H