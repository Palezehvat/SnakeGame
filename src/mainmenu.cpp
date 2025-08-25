#include "mainmenu.h"

namespace nMenu {
    Menu::Menu(QWidget* parent) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        background = QPixmap(QCoreApplication::applicationDirPath() 
                   + UISettings::backgroundPathMainMenu);

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
        QIcon iconSettings(QCoreApplication::applicationDirPath() 
                         + UISettings::settingsIconPathMainMenu);
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