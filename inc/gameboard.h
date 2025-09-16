/**
 * @file gameboard.h
 * @brief Игровая доска, состоящая из клеток
 */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QPixmap>
#include <QWidget>
#include "logger.h"
#include "uisettings.h"

/**
 * @namespace nGameBoard
 * @brief Содержит в себе класс GameBoard, перечисление TypeCell и структура Cell
 */
namespace nGameBoard{

/**
 * @enum TypeCell
 * @brief Перечисление для указания типа клетки на доске.
 *
 * Используется для различения разных типов клеток:
 * - камень(сейчас не  используется, нужен для будущих версий)
 * - трава
 * - еда
 * - змея
 */
enum TypeCell {
    grass,
    food,
    snake,
    rock
};

/**
 * @struct Cell
 * @brief Содержит информацию о конкретной клетки
 * 
 * Содержит в себе:
 * - строку, где находится клетка
 * - колонку, где находится клетка
 * - тип клетки
 */
struct Cell {
    int row;
    int col;
    TypeCell type;
};

/**
 * @class GameBoard
 * @brief Класс, ответственный за доску
 */
class GameBoard {
public:
    /// Конструктор
    GameBoard();
    /**
     * @brief Получение клетки по координатам
     * @param x Координата по оси абсцисс
     * @param y Координата по оси ординат
     * @return Клетка, по заданным координатам
     */
    const Cell& getCell(int x, int y) const;
    /**
     * @brief Назначение типа указанной клетке
     * @param x Координата по оси абсцисс
     * @param y Координата по оси ординат
     * @param type Новый тип клетки
     */
    void setCell(int x, int y, TypeCell type);
    /**
     * @brief Создание игровой доски
     * @param numberOfCellsInWidth Количество клеток в ширину
     * @param numberOfCellsInHeight Количество клеток в высоту
     */
    void createBoard(unsigned int numberOfCellsInWidth, unsigned int numberOfCellsInHeight);
    /// Получение вектора, состоящего из клеток, тип которых трава(ничем не занятые клетки)
    std::vector<QPoint> getEmptyCells() const;
    /**
     * @brief Перезапуск доски
     * @param width Ширина новой доски
     * @param height Высота новой доски
     */
    void restart(int width, int height);

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    QVector<QVector<Cell>> board;

    unsigned int numberOfCellsInHeight = 0;
    unsigned int numberOfCellsInWidth = 0;
};

};

#endif // GAMEBOARD_H