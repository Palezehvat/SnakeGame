#include "gamesettings.h"

namespace nGameSettings {
    GameSettings::GameSettings(std::shared_ptr<QSettings> settings, QWidget* parent) :
                               QWidget(parent), settings(settings) {
        logger = nLogger::Logger::getLogger();

        setAutoFillBackground(false);

        mainLayout = new QVBoxLayout(this);

        titleSettings = new QLabel("Настройки игры");
        titleSettings->setStyleSheet(UISettings::styleToLabel);

        grid = new QGridLayout();

        firstCreateConfig();

        unsigned int currentWidth  = settings->value("game/width", UISettings::maxWidth).toInt();
        unsigned int currentHeight = settings->value("game/height", UISettings::maxHeight).toInt();

        boardWidth = new nInternalsSettings::InternalsSettings("Ширина поля", currentWidth,
                        UISettings::minWidth, UISettings::maxWidth, "game/width", settings); 
        boardHeight = new nInternalsSettings::InternalsSettings("Высота поля", currentHeight,
                        UISettings::minHeight, UISettings::maxHeight, "game/height", settings);

        boardWidth->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        boardHeight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        
        grid->addWidget(boardWidth, 0, 0);
        grid->addWidget(boardHeight, 0, 1);
        
        grid->setColumnStretch(0, 1);
        grid->setColumnStretch(1, 1);
        grid->setRowStretch(0, 1);
        grid->setRowStretch(1, 1);

        QHBoxLayout* horizontalContentLayout = new QHBoxLayout();
        
        horizontalContentLayout->addStretch(1);
        horizontalContentLayout->addLayout(grid, 5);
        horizontalContentLayout->addStretch(1);

        toMainSettings = new QPushButton("Вернуться назад");
        connect(toMainSettings, &QPushButton::clicked, this, &GameSettings::switchToMainSettings);
        toMainSettings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        toMainSettings->setStyleSheet(UISettings::styleToButton);
        toMainSettings->setFont(titleSettings->font());

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(toMainSettings, 3);
        buttonLayout->addStretch(1);

        mainLayout->addWidget(titleSettings, 1, Qt::AlignHCenter);
        mainLayout->addStretch(1);
        mainLayout->addLayout(horizontalContentLayout, 2);
        mainLayout->addStretch(1);
        mainLayout->addLayout(buttonLayout, 1);

        logger->info("Класс GameSettings успешно инициализирован");
    }

    void GameSettings::firstCreateConfig() {
        if (!settings->contains("game/width"))
            settings->setValue("game/width", UISettings::maxWidth);

        if (!settings->contains("game/height"))
            settings->setValue("game/height", UISettings::maxHeight);
    }

    void GameSettings::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);

        if (auto* title = findChild<QLabel*>()) {
            int fontSize = height() / 25;
            if (fontSize > 0) {
                QFont font = title->font();
                font.setPointSize(fontSize);
                title->setFont(font);
            }
        }

        toMainSettings->setFont(titleSettings->font());
    }

    unsigned int GameSettings::getHeight() const {
        return boardHeight->getValue();
    }
    
    unsigned int GameSettings::getWidth() const {
        return boardWidth->getValue();
    }

}