#include "settings.h"

namespace nSettings {
    int Settings::length = 10;
    int Settings::width = 15;
    int Settings::sizeCell = 40;

    Settings::Settings(QWidget* parent) :QWidget(parent) {
        logger = Log::Logger::getLogger();
        QVBoxLayout* layout = new QVBoxLayout(this);
        QPushButton* toSettings = new QPushButton("Вернуться назад");
        layout->addWidget(toSettings);
        connect(toSettings, &QPushButton::clicked, this, &Settings::switchToMenu);
        logger->info("Класс Settings успешно инициализирован");
    }

    void Settings::resizeEvent(QResizeEvent* event) {
        //
    }

    int Settings::getLength() {
        return length;
    }
    
    int Settings::getWidth() {
        return width;
    }

    int Settings::getSizeCell() {
        return sizeCell;
    }
}