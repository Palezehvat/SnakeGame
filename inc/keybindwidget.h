/**
 * @file keybindwidget.h
 * @brief Общий вид настройки управления, управляемые пользователем
 */

#ifndef KEYBINDWIDGET_H
#define KEYBINDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include <QKeySequence>
#include <QSettings>
#include "uisettings.h"
#include "logger.h"

/**
 * @namespace nKeyBindWidget
 * @brief Содержит в себе класс KeyBindWidget
 */
namespace nKeyBindWidget {
/**
 * @class KeyBindWidget
 * @brief Визуально изменённый QPushButton для настроек управления пользователем
 */
class KeyBindWidget : public QPushButton {
    Q_OBJECT

public:
    /**
     * @brief Конструктор 
     * @param actionName Название настройки
     * @param currentKey Текущая клавиша(берётся из конфига)
     * @param settings Умный указатель на QSettings для работы с конфигом(настройки управления)
     * @param settingsPlace Путь в конфиге, где лежат настройки
     * @param placeInMap Ключ от keys(unordered_map со всеми выбранными настройками)
     * @param keys Умный указатель на unordered_map со всеми настройками
     * @param parent Родительский виджет (если nullptr — виджет верхнего уровня)
     */
    KeyBindWidget(const QString& actionName, const int currentKey,
                  std::shared_ptr<QSettings> settings, const QString& settingsPlace,
                  const QString& placeInMap, std::shared_ptr<std::unordered_map<QString, int>>keys,
                  QWidget* parent = nullptr);
    /// Получение выбранной клавиши для данной настройки
    int getKey() const;

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    std::shared_ptr<QSettings> settings = nullptr;
    std::shared_ptr<std::unordered_map<QString, int>> keys = nullptr;
    QString placeInMap;
    QString settingsPlace;
    QString action;
    int key = 0;
    bool waitingForKey = false;
    
    /// Обновление текста в настройке(для пользователя)
    void updateText();

protected:
    /**
     * @brief Основной метод класса, позволяющий пользователю изменять клавишу для выбранного действия в игре
     * @param event Указатель на событие клавиатуры (QKeyEvent)
     */
    void keyPressEvent(QKeyEvent *event) override;
    /// Изменение размеров виджета
    void resizeEvent(QResizeEvent* event) override;

signals:
    /// Сигнал, отправляемый в случае изменения клавиши выбранного действия
    void keyChanged(const QString& action, int key);

private slots:
    /// Слот, связанный с нажатием клавиши
    void onClicked();
};

}; // nKeyBindWidget

#endif // KEYBINDWIDGET_H