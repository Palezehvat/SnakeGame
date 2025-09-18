/**
 * @file gamesettings.h
 * @brief Настройки, связанные с игрой
 */

#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSettings>
#include "internalssettings.h"
#include "logger.h"
#include "uisettings.h"

/**
 * @namespace nGameSettings
 * @brief Содержит в себе класс GameSettings
 */
namespace nGameSettings {

/**
 * @class GameSettings
 * @brief Класс для работы с игровыми настройками
 * 
 * Игровые настройки:
 * - ширина поля(количество клеток)
 * - высота поля(количество клеток)
 */
class GameSettings : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param settings Умный указатель на QSettings для работы с конфигом(настройки управления)
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    GameSettings(std::shared_ptr<QSettings> settings, QWidget* parent = nullptr);
    /// Получение высоты поля(количество клеток)
    unsigned int getHeight() const;
    /// Получение ширины поля(количество клеток)
    unsigned int getWidth() const;

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    nInternalsSettings::InternalsSettings* boardWidth = nullptr;
    nInternalsSettings::InternalsSettings* boardHeight = nullptr;
    QLabel* titleSettings = nullptr;
    QGridLayout* grid = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPushButton* toMainSettings = nullptr;
    std::shared_ptr<QSettings> settings = nullptr;

    /// Инициализация конфига в случае его отсутствия
    void firstCreateConfig();

protected:
    /**
     * @brief Изменение размера игровых настроек
     * @param event Событие изменения размера окна настроек(передаётся системой Qt)
     */
    void resizeEvent(QResizeEvent* event) override;

signals:
    /// Сигнал для возврата к основным настройкам
    void switchToMainSettings();
};

} // namespace nGameSettings

#endif // GAMESETTINGS_H