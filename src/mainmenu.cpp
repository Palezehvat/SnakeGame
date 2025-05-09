#include "mainmenu.h"
#include <iostream>

namespace nMenu {
    Menu::Menu(QWidget* parent) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QString backgroundPath = QCoreApplication::applicationDirPath() + "/../images/background.png";
        QPixmap background(backgroundPath);

        logger = Log::Logger::getLogger(); 

        if (background.isNull()) {
            logger->error("Не удалось подгрузить картинку, на задний фон экрана(главное меню)");
        } else {
            logger->info("Картинка успешно подгружена");
            QPalette palette;
            this->setAutoFillBackground(true);
            palette.setBrush(QPalette::Window, background.scaled(size(), Qt::IgnoreAspectRatio));
            this->setPalette(palette);
        }

        startGame = new QPushButton("Start Game!", this);
        startGame->setFixedSize(200, 50);
        
        layout->addStretch();
        layout->addWidget(startGame, 0, Qt::AlignHCenter);
        layout->addStretch();

        toSettings = new QPushButton();
        toSettings->setFixedSize(50, 50);
        QString iconPath = QCoreApplication::applicationDirPath() + "/../images/settings.png";
        QIcon iconSettings(iconPath);
        toSettings->setIcon(iconSettings);
        toSettings->setIconSize(QSize(53, 53));
        toSettings->setFlat(true);
        toSettings->setStyleSheet("background-color: transparent; border: none;");
        layout->addWidget(toSettings);
        connect(toSettings, &QPushButton::clicked, this, &Menu::switchToSettings);
        connect(startGame, &QPushButton::clicked, this, &Menu::switchToGame);
        logger->info("Класс Menu успешно инициализирован");
    }

    void Menu::resizeEvent(QResizeEvent* event) {
        QString imagePath = QCoreApplication::applicationDirPath() + "/../images/background.png";
        QPixmap background(imagePath);
        if (background.isNull()) {
            logger->error("Не удалось подгрузить картинку, на задний фон экрана(главное меню),"
                        "во время изменения размера экрана");
        } else {
            background = background.scaled(this->size(), Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation);
        
            QPalette palette;
            palette.setBrush(QPalette::Window, QBrush(background));
            this->setPalette(palette);
        }
        logger->info("Размер начального окна успешно изменён");
    }
}