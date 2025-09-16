/**
 * @file gameview.h
 * @brief Логика, связанная с отрисовкой игры
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QPainter>
#include <QDateTime>
#include <QTimer>
#include <QKeyEvent>
#include <QPainterPath>
#include <QApplication>
#include <iostream>
#include <queue>
#include "logger.h"
#include "gameboard.h"
#include "food.h"
#include "snake.h"
#include "gamecontroller.h"
#include "uisettings.h"

namespace nGameController {
    class GameController;
}

/**
 * @namespace nGameView
 * @brief Содержит в себе класс GameView
 */
namespace nGameView {

class GameView : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param controller Контролер необходим для обработки работы клавиш
     * @param gameUpdateInterval Параметр, который нужен для отрисовки змеи в момент времени t
     * @param height Высота поля(количество клеток)
     * @param width Ширина поля(количество клеток)
     * @param keys Умный указатель на выбранные пользователем клавиши в настройках управления игрой
     * @param moves Умный указатель на очередь последующих движений змеи
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    GameView(nGameController::GameController* controller, int gameUpdateInterval,
             unsigned int height, unsigned int width,
             std::shared_ptr<std::unordered_map<QString, int>> keys, 
             std::shared_ptr<std::queue<nSnake::Movement>> moves, QWidget* parent = nullptr);
    /// Установка игровой доски для отрисовки
    void setGameBoard(std::shared_ptr<nGameBoard::GameBoard> board);
    /// Установка еды для отрисовки
    void setFood(std::shared_ptr<nFood::Food> food);
    /// Установка змеи для отрисовки
    void setSnake(std::shared_ptr<nSnake::Snake> snake);
    /// Установка времени, когда было последнее движение змеи
    void setLastMoveTime(qint64 lastMoveTime);
    /// Получение для размера виджета наилучшей ширины
    int getPreferredWidth() const;
    /// Получение для размера виджета наилучшей ширины
    int getPreferredHeight() const;
    /**
     * @brief Остановка анимации
     * 
     * Анимация останавливается в момент, когда змея доходит до центра ближайшей клетки назначения
     */
    void stopAnimation();
    /// Возобновление анимации
    void continueAnimation();
    /**
     * @brief Перезапуск отрисовки(новая игра)
     * @param height Высота поля(количество клеток)
     * @param width Ширина поля(количество клеток)
     */
    void restart(unsigned int height, unsigned int width);
    /**
     * @brief Указание на то, что змея врезалась(или в стенку, или в себя)
     * @param t Оптимальный вычисленный параметр для более красивой отрисовки 
     */
    void setCollision(qreal t);
    /**
     * @brief Вычисление оптимального параметра отрисовки, когда змея врезалась(или в стенку, или в себя)
     * @param head Местоположение головы(до того, как она врезалась)
     * @param dir Направление движения змеи
     */
    qreal computeCollision(const QPoint& head, nSnake::Movement dir);

private:
    bool collisionAnimation = false;
    qreal collision = 1.0;
    QColor colorEvenField;
    QColor colorOddField;
    QColor colorBackground;
    qreal epsilon = 0.0;
    qreal headRenderAngle = 0.0;
    bool headAngleInitialized = false;
    qreal sizeCell = 0.0;
    unsigned int heightBoard = 0;
    unsigned int widthBoard = 0;
    qreal widthBody = 0.0;
    bool animationFrozen = false;
    qreal pausedT = 1.0;
    std::shared_ptr<std::vector<QPoint>> currBodySnake = nullptr;
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::shared_ptr<nGameBoard::GameBoard> gameboard = nullptr;
    std::shared_ptr<nFood::Food> food = nullptr;
    std::shared_ptr<nSnake::Snake> snake = nullptr;
    nGameController::GameController* controller = nullptr;
    std::shared_ptr<std::unordered_map<QString, int>> keys = nullptr;
    std::shared_ptr<std::queue<nSnake::Movement>> moves = nullptr;
    QTimer* frameTimer = nullptr;
    qint64 lastMoveTime = 0;
    int gameUpdateIntervalMs = 0;

    /**
     * @brief Основной метод отрисовки
     * @param event Событие перерисовки, содержащее область для обновления.
     * 
     * Ответственен за отрисовку:
     * - поля
     * - доски из клеток
     * - еды
     * - змеи
     */
    void paintEvent(QPaintEvent* event) override;
    /// Изменение размера окна
    void resizeEvent(QResizeEvent* event) override;
    /// Отрисовка доски
    void drawBoard(QPainter& p);
    /// Отрисовка яблока
    void drawApple(QPainter& p, QPointF center);
    /**
     * @brief Подготовка к отрисовке еды
     * @param p QPainter, с помощью которого выполняется рисование
     * 
     * Здесь идёт получение позиции, где должна быть отрисована еда. Сама отрисовка осуществляется в другом методе drawApple()
     * @see drawApple()
     */
    void drawFood(QPainter& p);
    /**
     * @brief Отрисовка тела змеи(без головы и глаз)
     * @param p QPainter, с помощью которого выполняется рисование
     */
    void drawSnake(QPainter& p);
    /**
     * @brief Отрисовка глаз змеи(с поворотом в случае необходимости)
     * @param p QPainter, с помощью которого выполняется рисование
     * @param p1 Точка, где должен быть расположен глаз змеи
     * @param p2 Точка, где должен быть расположен глаз змеи
     */
    void drawEyes(QPainter& p, QPointF p1, QPointF p2);
    /**
     * @brief Отрисовка головы змеи(с поворотом в случае необходимости)
     * @param center Точка центра головы
     * @param angle Угол поворота головы
     */
    void drawRotatedHead(QPainter& p, QPointF center, qreal angle);
    /**
     * @brief Считывание нажатия клавиш
     * @param event Указатель на объект QKeyEvent, содержащий информацию о нажатой клавише
     * 
     * Действия, которые обрабатываются:
     * - движения(влево, вправо, вверх, вниз)
     * - пауза(одна и та же кнопка отвечает за включение и отключение паузы)
     * - перезапуск
     * 
     * Информация о нажатой клавише отправляется в контроллер(nGameController::GameController)
     * @see nGameController::GameController
     */
    void keyPressEvent(QKeyEvent* event);
    /// Возвращает предпочтительный размер виджета для менеджера компоновки
    QSize sizeHint() const override;
    /// Возвращает минимальный рекомендуемый размер виджета для менеджера компоновки
    QSize minimumSizeHint() const;
};

}; // nGameBoard

#endif //GAMEVIEW_H