/**
 * @file mainmenu.h
 * @brief Основное меню программы(то, что видит пользователь при запуске программы) 
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "logger.h"
#include "uisettings.h"

/**
 * @namespace nMenu
 * @brief Содержит в себе класс Menu
 */
namespace nMenu {

/**
 * @class Menu
 * @brief Ответственен за визуальное отображение начального меню
 */
class Menu : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    Menu(QWidget* parent = nullptr);

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    QPushButton* startGame = nullptr;
    QPushButton* toSettings = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPixmap background;
    
    /// Отрисовка заднего фона меню
    void showBackground();

protected:
    /// Изменение размера меню
    void resizeEvent(QResizeEvent* event) override;

signals:
    /// Сигнал для смены меню на настройки
    void switchToSettings();
    /// Сигнал для смены меню на игру
    void switchToGame();
};

}; // nMenu


#endif // MENU_H