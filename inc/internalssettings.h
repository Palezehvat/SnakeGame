/**
 * @file internalssettings.h
 * @brief Общий вид настройки игры, управляемые пользователем
 */

#ifndef INTERNALSSETTINGS_H
#define INTERNALSSETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPainter>
#include <QEvent>
#include <QSettings>
#include "uisettings.h"
#include "logger.h"

/**
 * @namespace nInternalsSettings
 * @brief Содержит в себе класс InternalsSettings
 */
namespace nInternalsSettings {
/**
 * @class InternalsSettings
 * @brief Визуально изменённый QSlider для настроек игры пользователем
 */
class InternalsSettings : public QSlider {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param newText Текст, наложенный поверх QSlider
     * @param newValue Текущее значение QSlider
     * @param newMinValue Минимальное значение QSlider
     * @param newMaxValue Максимальное значение QSlider
     * @param settingsPlace Путь в конфиге, где лежат настройки
     * @param settings Умный указатель на QSettings для работы с конфигом(настройки управления)
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    InternalsSettings(const QString& newText, const unsigned int newValue, const 
        unsigned int newMinValue, const unsigned int newMaxValue, const QString& settingsPlace,
        std::shared_ptr<QSettings> settings, QSlider* parent = nullptr);
    
    /// Изменение размера виджета
    void resizeEvent(QResizeEvent* event);
    /// Получение текущего значения виджета
    unsigned int getValue() const;

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::shared_ptr<QSettings> settings = nullptr;
    unsigned int value = 0;
    double fontSize = 0;
    bool isHovered = false;
    QString settingsPlace;
    QString text;

protected:
    /// Отрисовка текста поверх QSlider
    void paintEvent(QPaintEvent* event) override;
    /// Изменение виджета при его использовании 
    void enterEvent(QEnterEvent* event) override;
    /// Изменение виджета после того, как его использовали
    void leaveEvent(QEvent* event) override;
};

}

#endif //INTERNALSSETTINGS_H