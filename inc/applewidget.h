/**
 * @file applewidget.h
 * @brief Отрисовка яблока и количество съеденных яблок 
 */

#ifndef APPLEWIDGET_H
#define APPLEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include "logger.h"
#include "uisettings.h"

/**
 * @namespace nAppleWidget
 * @brief Содержит в себе класс AppleWidget
 */
namespace nAppleWidget {
/**
 * @class AppleWidget
 * @brief Класс для подсчёта съеденных яблок 
 */
class AppleWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    AppleWidget(QWidget* parent = nullptr);
    /// Увеличивает счётчик на единицу и отображает изменения на экране
    void updateCounter();
    /// Сбрасывает счётчик и отображает изменения на экране
    void restartCounter();
    
protected:
    /**
     * @brief Отрисовка яблока и счёта
     * @param event Событие перерисовки (передаётся системой Qt)
     */
    void paintEvent(QPaintEvent* event) override;
    
private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    int counter = 0;

    /**
     * @brief Отрисовка яблока
     * @param p QPainter, с помощью которого выполняется рисование
     * @param center Точка центра яблока
     * @param r Радиус яблока
     */
    void drawApple(QPainter& p, QPoint center, const qreal r);
};

};


#endif // APPLEWIDGET_H