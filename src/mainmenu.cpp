#include "mainmenu.h"
#include <iostream>

namespace nMenu {
    Menu::Menu(QWidget* parent) : QWidget(parent) {
        logger = nLogger::Logger::getLogger();

        mainLayout = new QVBoxLayout(this);

        showBackground();
        int sizeBorder = std::min(height(), width()) / 100;

        startGame = new QPushButton("Играть");
        startGame->setStyleSheet(UISettings::styleToMenuButtons.arg(QString::number(sizeBorder)));
        startGame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        toSettings = new QPushButton("Настройки");
        toSettings->setStyleSheet(UISettings::styleToMenuButtons.arg(QString::number(sizeBorder)));
        toSettings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QHBoxLayout* layoutForSettingsAndStartGame = new QHBoxLayout();
        layoutForSettingsAndStartGame->addWidget(startGame, 2);
        layoutForSettingsAndStartGame->addStretch(2);
        layoutForSettingsAndStartGame->addWidget(toSettings, 2);

        mainLayout->addStretch(5);
        mainLayout->addLayout(layoutForSettingsAndStartGame, 2);

        connect(toSettings, &QPushButton::clicked, this, &Menu::switchToSettings);
        connect(startGame, &QPushButton::clicked, this, &Menu::switchToGame);
        logger->info("Класс Menu успешно инициализирован");
    }

    void Menu::showBackground() {
        background = QPixmap(QCoreApplication::applicationDirPath() 
        + UISettings::backgroundPathMainMenu);

        if (background.isNull()) {
            logger->error("Не удалось подгрузить картинку, на задний фон экрана(главное меню)");
        } else {
            logger->info("Картинка успешно подгружена");
            QPalette palette;
            this->setAutoFillBackground(true);
            palette.setBrush(QPalette::Window, background.scaled(size(), Qt::IgnoreAspectRatio));
            this->setPalette(palette);
        }
    }

    void Menu::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);
        if (!background.isNull()) {
            QPalette palette;
            QPixmap scaled = background.scaled(this->size(),
             Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            palette.setBrush(QPalette::Window, scaled);
            this->setPalette(palette);
        }

        int fontSize = startGame->height() / 5;
        if (fontSize > 0) {
            QFont font = startGame->font();
            font.setPointSize(fontSize);
            startGame->setFont(font);

            font = toSettings->font();
            font.setPointSize(fontSize);
            toSettings->setFont(font);
        }

        int sizeBorder = std::min(height(), width()) / 100;
        toSettings->setStyleSheet(UISettings::styleToMenuButtons.arg(QString::number(sizeBorder)));
        startGame->setStyleSheet(UISettings::styleToMenuButtons.arg(QString::number(sizeBorder)));

        logger->info("Размер начального окна в меню успешно изменён");
    }
}