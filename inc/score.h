/**
 * @file score.h
 * @brief Обёртка над счётом для игры
 */

#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include "logger.h"
#include "applewidget.h"
#include "uisettings.h"

/**
 * @namespace nScore
 * @brief Содержит в себе класс Score
 */
namespace nScore {

/**
 * @class Score
 * @brief Класс обёртка отвечает за подсчёт съеденной еды в текущей игре, отрисовка счёта происходит в nAppleWidget::AppleWidget
 * @see nAppleWidget::AppleWidget
 */
class Score : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    Score(QWidget* parent = nullptr);
    /// Увеличивает счётчик на 1
    void updateCounter();
    /// Перезапуск счётчика
    void restart();

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    unsigned long long counter = 0;
    QPushButton* restartButton = nullptr;
    QPushButton* menuButton = nullptr;
    QPushButton* pauseButton = nullptr;
    std::unique_ptr<nAppleWidget::AppleWidget> apple = nullptr;

protected:
    /// Изменение размера счёта
    void resizeEvent(QResizeEvent* event) override;
    /// Отрисовка заднего фона
    void paintEvent(QPaintEvent* event) override;

signals:
    /// Сигнал для смены текущего виджета на меню
    void backToMenu();
    /// Сигнал для перезапуска игры
    void restartGame();
    /// Сигнал для включения и выключения паузы
    void pause();

};

} // nScore

#endif // SCORE_H