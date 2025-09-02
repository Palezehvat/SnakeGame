#include "mainsettings.h"

namespace nMainSettings {
    MainSettings::MainSettings(QWidget* parent) : QWidget(parent) {
        logger = Log::Logger::getLogger();

        setAutoFillBackground(false);

        // Горизонтально: 7
        // Вертикально: 6

        mainLayout = new QVBoxLayout(this);

        titleSettings = new QLabel("Настройки");
        titleSettings->setStyleSheet(UISettings::styleToLabel);

        grid = new QGridLayout();

        toControlSettings = new QPushButton("Управление");
        toGameSettings = new QPushButton("Игровые настройки");

        connect(toControlSettings, &QPushButton::clicked, this,
                &MainSettings::switchToControlSettings);
        connect(toGameSettings, &QPushButton::clicked, this,
                &MainSettings::switchToGameSettings);

        toControlSettings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        toGameSettings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        toControlSettings->setStyleSheet(UISettings::styleToButton);
        toGameSettings->setStyleSheet(UISettings::styleToButton);
        
        grid->addWidget(toGameSettings, 0, 0);
        grid->addWidget(toControlSettings, 0, 1);
        
        grid->setColumnStretch(0, 1);
        grid->setColumnStretch(1, 1);

        QHBoxLayout* horizontalContentLayout = new QHBoxLayout();
        
        horizontalContentLayout->addStretch(1);
        horizontalContentLayout->addLayout(grid, 5);
        horizontalContentLayout->addStretch(1);

        toMenu = new QPushButton("Вернуться назад");

        connect(toMenu, &QPushButton::clicked, this, &MainSettings::switchToMenu);
        
        toMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        toMenu->setStyleSheet(UISettings::styleToButton);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(toMenu, 3);
        buttonLayout->addStretch(1);

        mainLayout->addWidget(titleSettings, 1, Qt::AlignHCenter);
        mainLayout->addStretch(1);
        mainLayout->addLayout(horizontalContentLayout, 2);
        mainLayout->addStretch(1);
        mainLayout->addLayout(buttonLayout, 1);

        logger->info("Класс MainSettings успешно инициализирован");
    }

    void MainSettings::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);

        if (auto* title = findChild<QLabel*>()) {
            int fontSize = height() / 25;
            if (fontSize > 0) {
                QFont font = title->font();
                font.setPointSize(fontSize);
                title->setFont(font);
            }
        }

        toMenu->setFont(titleSettings->font());

        int fontSize = height() / 25;
        if (fontSize > 0) {
            QFont font = toControlSettings->font();
            font.setPointSize(fontSize);
            toControlSettings->setFont(font);
            font = toGameSettings->font();
            font.setPointSize(fontSize);
            toGameSettings->setFont(font);
        }
    }

}