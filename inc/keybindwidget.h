#ifndef KEYBINDWIDGET_H
#define KEYBINDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QKeyEvent>
#include <QKeySequence>
#include <QSettings>
#include "uisettings.h"
#include "logger.h"

namespace nKeyBindWidget {

class KeyBindWidget : public QPushButton {
    Q_OBJECT

public:
    KeyBindWidget(const QString& actionName, const int currentKey,
                  std::shared_ptr<QSettings> settings, const QString& settingsPlace,
                  const QString& placeInMap, std::shared_ptr<std::unordered_map<QString, int>>keys,
                  QWidget* parent = nullptr);
    int getKey() const;

private:
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<QSettings> settings = nullptr;
    std::shared_ptr<std::unordered_map<QString, int>> keys;
    QString placeInMap;
    QString settingsPlace;
    QString action;
    int key;
    bool waitingForKey;
    
    void updateText();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

signals:
    void keyChanged(const QString& action, int key);

private slots:
    void onClicked();
};

}; // nKeyBindWidget

#endif // KEYBINDWIDGET_H