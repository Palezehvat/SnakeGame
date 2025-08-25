#include "settings.h"

namespace nSettings {
    Settings::Settings(QWidget* parent) : QWidget(parent) {
        logger = Log::Logger::getLogger();

        mainLayout = new QVBoxLayout(this);
        background = QPixmap(QCoreApplication::applicationDirPath() 
                           + UISettings::backgroundPathSettings);

        if (background.isNull()) {
            logger->error("Не удалось подгрузить картинку, на задний фон экрана(настройки)");
        } else {
            logger->info("Картинка успешно подгружена");
            QPalette palette;
            this->setAutoFillBackground(true);
            palette.setBrush(QPalette::Window, background.scaled(size(), Qt::IgnoreAspectRatio));
            this->setPalette(palette);
        }

        QLabel* titleSettings = new QLabel("Настройки");
        QString color = "#1c89c4";
        QString styleTitleSettings = QString(R"(
            QLabel {
                color: %1;
                font-weight: bold;
            }
        )").arg(UISettings::textColor);


        titleSettings->setStyleSheet(styleTitleSettings);
        titleSettings->setAlignment(Qt::AlignCenter);

        grid = new QGridLayout();
        boardWidth = new nInternalsSettings::InternalsSettings("Ширина поля",
                            UISettings::maxWidth, UISettings::minWidth, UISettings::maxWidth); 
        boardHeight = new nInternalsSettings::InternalsSettings("Высота поля",
                            UISettings::maxHeight, UISettings::minHeight, UISettings::maxHeight);
        //countRocks = new nInternalsSettings::InternalsSettings("Количество камней", 0, 0, 148);
        
        grid->addWidget(boardWidth, 0, 0);
        //grid->addWidget(countRocks, 1, 0);
        grid->addWidget(boardHeight, 0, 1);
        
        grid->setColumnStretch(0, 1);
        grid->setColumnStretch(1, 1);

        QHBoxLayout* horizontalContentLayout = new QHBoxLayout();
        
        horizontalContentLayout->addStretch(1);
        horizontalContentLayout->addLayout(grid, 3);
        horizontalContentLayout->addStretch(1);

        toSettings = new QPushButton("Вернуться назад");
        connect(toSettings, &QPushButton::clicked, this, &Settings::switchToMenu);
        toSettings->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QString styleToSettings = QString(R"(
            QPushButton {
                background-color: %1;
                padding: 6px;
                border: 1px solid white;
                color: %2;
            }
            QPushButton:hover {
                background-color: %3
            }
        )").arg(UISettings::buttonBackgroundColor, UISettings::textColor,
            UISettings::hoverTextColor);

        toSettings->setStyleSheet(styleToSettings);

        mainLayout->addWidget(titleSettings, 1);
        mainLayout->addStretch();
        mainLayout->addLayout(horizontalContentLayout, 8);
        mainLayout->addWidget(toSettings, 1);
        mainLayout->addStretch();
        mainLayout->setAlignment(toSettings, Qt::AlignCenter);

        logger->info("Класс Settings успешно инициализирован");
    }

    void Settings::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);

        if (auto* title = findChild<QLabel*>()) {
            int fontSize = height() / 25;
            if (fontSize > 0) {
                QFont font = title->font();
                font.setPointSize(fontSize);
                title->setFont(font);
            }
        }

        if (auto* button = findChild<QPushButton*>()) {
            int fontSize = height() / 25;
            if (fontSize > 0) {
                QFont font = button->font();
                font.setPointSize(fontSize);
                button->setFont(font);
            }
        }

        if (!background.isNull()) {
            QPalette palette;
            QPixmap scaled = background.scaled(this->size(),
             Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            palette.setBrush(QPalette::Window, scaled);
            this->setPalette(palette);
        }
    }

    unsigned int Settings::getHeight() {
        return boardHeight->getValue();
    }
    
    unsigned int Settings::getWidth() {
        return boardWidth->getValue();
    }

}