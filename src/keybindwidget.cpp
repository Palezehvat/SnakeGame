#include "keybindwidget.h"
#include <iostream>

namespace nKeyBindWidget {
    KeyBindWidget::KeyBindWidget(const QString& actionName, const int currentKey,
    std::shared_ptr<QSettings> settings, const QString& settingsPlace, const QString& placeInMap,
    std::shared_ptr<std::unordered_map<QString, int>> keys, QWidget* parent) : QPushButton(parent),
    action(actionName), settings(settings), settingsPlace(settingsPlace), keys(keys),
    placeInMap(placeInMap) {
        logger = Log::Logger::getLogger();
        key = currentKey;
        this->setStyleSheet(UISettings::styleToButton);
        waitingForKey = false;
        setFocusPolicy(Qt::StrongFocus);
        updateText();
        connect(this, &QPushButton::clicked, this, &KeyBindWidget::onClicked);
    }

    int KeyBindWidget::getKey() const {
        return key;
    }
    
    void KeyBindWidget::updateText() {
        setText(action + ": " + QKeySequence(key).toString());
    }

    void KeyBindWidget::onClicked() {
        waitingForKey = true;
        setText(action + ": ...");
    }

    void KeyBindWidget::keyPressEvent(QKeyEvent *event) {
        if (waitingForKey) {
            key = event->key();
            waitingForKey = false;
            settings->setValue(settingsPlace, key);
            (*keys)[placeInMap] = key;
            updateText();
            emit keyChanged(action, key);
        } else {
            QPushButton::keyPressEvent(event);
        }
    }

    void KeyBindWidget::resizeEvent(QResizeEvent* event) {
        QFont font = this->font();
        int fontSize = height() / 3;
        font.setPointSize(fontSize);
        this->setFont(font);
    }
}