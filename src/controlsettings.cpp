#include "controlsettings.h"
#include <iostream>

namespace nControlSettings {
    ControlSettings::ControlSettings(std::shared_ptr<QSettings> settings,
                                     QWidget* parent) : QWidget(parent), settings(settings) {
        logger = nLogger::Logger::getLogger();

        setAutoFillBackground(false);

        mainLayout = new QVBoxLayout(this);

        titleSettings = new QLabel("Настройки управления");

        titleSettings->setStyleSheet(UISettings::styleToLabel);
        titleSettings->setAlignment(Qt::AlignCenter);

        grid = new QGridLayout();

        keys = std::make_shared<std::unordered_map<QString, int>>();

        firstCreateConfig();

        int leftKey    = settings->value("control/left",     Qt::Key_A).toInt();
        int rightKey   = settings->value("control/right",    Qt::Key_D).toInt();
        int upKey      = settings->value("control/up",       Qt::Key_W).toInt();
        int downKey    = settings->value("control/down",     Qt::Key_S).toInt();
        int pauseKey   = settings->value("control/pause",    Qt::Key_E).toInt();
        int restartKey = settings->value("control/restart",  Qt::Key_R).toInt();

        keys->emplace("left", leftKey);
        keys->emplace("right", rightKey);
        keys->emplace("up", upKey);
        keys->emplace("down", downKey);
        keys->emplace("pause", pauseKey);
        keys->emplace("restart", restartKey);

        left    = new nKeyBindWidget::KeyBindWidget("Влево", leftKey, settings, "control/left", "left", keys);
        right   = new nKeyBindWidget::KeyBindWidget("Вправо", rightKey, settings, "control/right", "right", keys);
        up      = new nKeyBindWidget::KeyBindWidget("Вверх", upKey, settings, "control/up", "up", keys);
        down    = new nKeyBindWidget::KeyBindWidget("Вниз", downKey, settings, "control/down", "down", keys);
        pause   = new nKeyBindWidget::KeyBindWidget("Пауза", pauseKey, settings, "control/pause", "pause", keys);
        restart = new nKeyBindWidget::KeyBindWidget("Перезапуск", restartKey, settings,
                                                    "control/restart", "restart", keys);

        left->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        right->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        up->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        down->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        pause->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        restart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        
        grid->addWidget(left, 0, 0);
        grid->addWidget(right, 0, 1);
        grid->addWidget(up, 1, 0);
        grid->addWidget(down, 1, 1);
        grid->addWidget(pause, 2, 0);
        grid->addWidget(restart, 2, 1);
        
        grid->setColumnStretch(0, 1);
        grid->setColumnStretch(1, 1);
        grid->setRowStretch(0, 1);
        grid->setRowStretch(1, 1);
        grid->setRowStretch(2, 1);

        QHBoxLayout* horizontalContentLayout = new QHBoxLayout();
        
        horizontalContentLayout->addStretch(1);
        horizontalContentLayout->addLayout(grid, 3);
        horizontalContentLayout->addStretch(1);

        toMainSettings = new QPushButton("Вернуться назад");
        connect(toMainSettings, &QPushButton::clicked, this,
                &ControlSettings::switchToMainSettings);  // UpdateText у всех
        
        toMainSettings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        toMainSettings->setStyleSheet(UISettings::styleToButton);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(toMainSettings, 3);
        buttonLayout->addStretch(1);


        mainLayout->addWidget(titleSettings, 1, Qt::AlignHCenter);
        mainLayout->addStretch(1);
        mainLayout->addLayout(horizontalContentLayout, 2);
        mainLayout->addStretch(1);
        mainLayout->addLayout(buttonLayout, 1);

        logger->info("Класс ControlSettings успешно инициализирован");
    }

    void ControlSettings::firstCreateConfig() {
        if (!settings->contains("control/left"))
            settings->setValue("control/left", Qt::Key_A);

        if (!settings->contains("control/right"))
            settings->setValue("control/right", Qt::Key_D);

        if (!settings->contains("control/up"))
            settings->setValue("control/up", Qt::Key_W);

        if (!settings->contains("control/down"))
            settings->setValue("control/down", Qt::Key_S);

        if (!settings->contains("control/pause"))
            settings->setValue("control/pause", Qt::Key_E);

        if (!settings->contains("control/restart"))
            settings->setValue("control/restart", Qt::Key_R);
    }

    void ControlSettings::resizeEvent(QResizeEvent* event) {
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

    std::shared_ptr<std::unordered_map<QString, int>> ControlSettings::getKeys() {
        return keys;
    }
}