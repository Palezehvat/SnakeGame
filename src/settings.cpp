#include "settings.h"

namespace nSettings {
    int Settings::length = 10;
    int Settings::width = 15;

    Settings::Settings(QWidget* parent) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QPushButton* toSettings = new QPushButton("Вернуться назад");
        layout->addWidget(toSettings);
        connect(toSettings, &QPushButton::clicked, this, &Settings::switchToMenu);
    }

    void Settings::resizeEvent(QResizeEvent* event) {
        //
    }

    int Settings::getLength() {
        return length;
    };
    
    int Settings::getWidth() {
        return width;
    };
}