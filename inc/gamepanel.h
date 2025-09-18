/**
 * @file gamepanel.h
 * @brief Визуальное объедение счёта и игровой части(поля)
 */

#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "score.h"
#include "logger.h"

namespace nGameView {
    class GameView;
}

/**
 * @namespace nGamePanel
 * @brief Содержит в себе класс GamePanel
 */
namespace nGamePanel {

/**
 * @class GamePanel
 * @brief Класс для визуального объединения счёта и игровой части(поля)
 */
class GamePanel : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param board Игровая часть
     * @param score Счёт
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    GamePanel(std::shared_ptr<nGameView::GameView> board,
              std::shared_ptr<nScore::Score> score, QWidget* parent = nullptr);
    /// Возвращает игровую часть
    std::shared_ptr<nGameView::GameView> getBoard() const;

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::shared_ptr<nGameView::GameView> board = nullptr;
    std::shared_ptr<nScore::Score> score = nullptr;

    QHBoxLayout* layout = nullptr;

signals:
    /// Сигнал для возвращения в меню
    void backToMenu();
    /// Сигнал для перезапуска игры
    void restartGame();
    /// Сигнал об окончании игры
    void gameOver();

};

}; // nGamePanel

#endif // GAMEPANEL_H