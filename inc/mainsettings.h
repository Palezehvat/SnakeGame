/**
 * @file mainsettings.h
 * @brief Общие настройки
 */

#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "logger.h"
#include "uisettings.h"

/**
 * @namespace nMainSettings
 * @brief Содержит в себе класс MainSettings
 */
namespace nMainSettings {
/**
 * @class MainSettings
 * @brief Класс для визуальной страницы перехода к настройкам управления или настройкам игры
 */
class MainSettings : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    MainSettings(QWidget* parent = nullptr);

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    QGridLayout* grid = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPushButton* toMenu = nullptr;
    QPushButton* toControlSettings = nullptr;
    QPushButton* toGameSettings = nullptr;
    QLabel* titleSettings = nullptr;

protected:
    /// Изменение размера виджета
    void resizeEvent(QResizeEvent* event) override;

signals:
    /// Сигнал для смены общих настроек на меню
    void switchToMenu();
    /// Сигнал для смены общих настроек на настройки управления
    void switchToControlSettings();
    /// Сигнал для смены общих настроек на настройки игры
    void switchToGameSettings();
};

} // namespace nMainSettings

#endif // MAINSETTINGS_H
