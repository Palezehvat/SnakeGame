/**
 * @file settings.h
 * @brief Обёртка над общими настройками, настройками игры, настройками управления
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPalette>
#include <QStackedWidget>
#include <QSettings>
#include "logger.h"
#include "mainsettings.h"
#include "gamesettings.h"
#include "controlsettings.h"

/**
 * @namespace nSettings
 * @brief Содержит в себе класс Settings
 */
namespace nSettings {
/**
 * @class Settings
 * @brief Класс обёртка над общими настройками, настройками игры, настройками управления
 */
class Settings : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    Settings(QWidget* parent = nullptr);
    /// Получение высоты поля(количество клеток)
    unsigned int getHeight() const;
    /// Получение широты поля(количество клеток)
    unsigned int getWidth() const;
    /// Получение выбранных настроек управления
    std::shared_ptr<std::unordered_map<QString, int>> getKeys();

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    nMainSettings::MainSettings* mainSettings = nullptr;
    nGameSettings::GameSettings* gameSettings = nullptr;
    nControlSettings::ControlSettings* controlSettings = nullptr;
    std::shared_ptr<QSettings> settings = nullptr;
    QStackedWidget* stackedWidget = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPixmap background;

    /// Устанавливает задний фон для всех настроек(общие настройки, настройки управления, настройки игры)
    void showBackground();

protected:
    /// Изменение размера виджета 
    void resizeEvent(QResizeEvent* event) override;

signals:
    /// Сигнал для смены текущего виджета на меню
    void switchToMenu();
};

} // namespace nSettings

#endif // SETTINGS_H
