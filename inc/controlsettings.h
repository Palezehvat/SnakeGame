/**
 * @file controlsettings.h
 * @brief Страница настроек управления игры 
 */

#ifndef CONTROLSETTINGS_H
#define CONTROLSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>
#include "logger.h"
#include "keybindwidget.h"
#include "uisettings.h"

/**
 * @namespace nControlSettings
 * @brief Содержит в себе класс ControlSettings
 */
namespace nControlSettings {
/**
 * @class ControlSettings
 * @brief Класс для настроек управления пользователем
 */
class ControlSettings : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param settings Умный указатель на QSettings для работы с конфигом(настройки управления)
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    ControlSettings(std::shared_ptr<QSettings> settings, QWidget* parent = nullptr);
    /// Получение выбранных настроек управления
    std::shared_ptr<std::unordered_map<QString, int>> getKeys();

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    QGridLayout* grid = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPushButton* toMainSettings = nullptr;
    QLabel* titleSettings = nullptr;
    nKeyBindWidget::KeyBindWidget* left = nullptr;
    nKeyBindWidget::KeyBindWidget* right = nullptr;
    nKeyBindWidget::KeyBindWidget* up = nullptr;
    nKeyBindWidget::KeyBindWidget* down = nullptr;
    nKeyBindWidget::KeyBindWidget* pause = nullptr;
    nKeyBindWidget::KeyBindWidget* restart = nullptr;
    std::shared_ptr<QSettings>  settings = nullptr;
    std::shared_ptr<std::unordered_map<QString, int>> keys = nullptr;

    /// Инициализация конфига в случае его отсутствия
    void firstCreateConfig();

protected:
    /**
     * @brief Изменение размера настроек управления
     * @param event Событие изменения размера окна настроек(передаётся системой Qt)
     */
    void resizeEvent(QResizeEvent* event) override;

signals:
    /// Сигнал для возврата к основным настройкам
    void switchToMainSettings();
};

} // namespace nSettings

#endif // CONTROLSETTINGS_H
