/**
 * @file gamecontroller.h
 * @brief Управление логикой игры
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <queue>
#include "settings.h"
#include "gameboard.h"
#include "food.h"
#include "snake.h"
#include "logger.h"
#include "gameview.h" 
#include "score.h"
#include "gamepanel.h"

namespace nGameView {
    class GameView;
}

/**
 * @namespace nGameController
 * @brief Содержит в себе класс GameController
 */
namespace nGameController {

/**
 * @class GameController
 * @brief Класс, управляющий логикой игры
 */
class GameController : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param settings Настройки, которыми управляет пользователь
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    explicit GameController(std::shared_ptr<nSettings::Settings> settings,
                            QObject* parent = nullptr);
    /**
     * @brief Запускает игру
     * @return Панель, включающую счёт и игровую часть
     * 
     * Инициализация основных компонентов с последующим запуском
     */
    std::shared_ptr<nGamePanel::GamePanel> startGame();
    /**
     * @brief Обновление логики(gamecontroller) каждые gameUpdateIntervalMs
     * 
     * Ответственен за:
     * - проверку съела ли змея еду
     * - указания змее о необходимости расти в случае поедания еды
     * - указание о создание новой еды в пустой клетки, если еда была съедена
     * - проверка завершения игры
     * - изменение направления движения змеи 
     */
    void update();
    /// Запуск новой игры
    void restart();
    /// Установка паузы
    void setPause();
    /**
     * @brief Изменение направления движения змеи
     * @param newDirection Новое направление движения
     */
    void changeDirection(nSnake::Movement newDirection);
private:
    std::shared_ptr<nGameBoard::GameBoard> gameBoard = nullptr;
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::shared_ptr<nSnake::Snake> snake = nullptr;
    std::shared_ptr<nFood::Food> food = nullptr;
    std::shared_ptr<nGameView::GameView> board = nullptr;
    std::shared_ptr<nScore::Score> score = nullptr;
    std::shared_ptr<nGamePanel::GamePanel> panel = nullptr;
    std::shared_ptr<nSettings::Settings> settings = nullptr;
    std::shared_ptr<std::queue<nSnake::Movement>> moves = nullptr;
    std::shared_ptr<std::vector<QPoint>> currBodySnake = nullptr;

    unsigned int numberOfCellsInHeight = 0;
    unsigned int numberOfCellsInWidth = 0;

    qint64 lastMoveTime = 0;
    int gameUpdateIntervalMs = 300;
    QTimer* gameTimer = nullptr;
    bool isPause = false;
    bool isGameOver = false;

    /**
     * @brief Инициализация доски
     * @param numberOfCellsInWidth Количество клеток в ширину
     * @param numberOfCellsInHeight Количество клеток в высоту
     */
    void initBoard(unsigned int numberOfCellsInWidth,
                   unsigned int numberOfCellsInHeight);
    /// Создание еды в пустой клетки, если еда была съедена
    void spawnFood();
    /**
     * @brief Очищает очередь запланированных движений
     * @param moves Очередь движений змеи
     */
    void clearQueueOfMoves(std::shared_ptr<std::queue<nSnake::Movement>>& moves);               
signals:
    /// Сигнал о завершении игры
    void gameOver();
}; // GameController

}; // nGameController

#endif // GAMECONTROLLER_H