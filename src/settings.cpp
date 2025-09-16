#include "settings.h"

namespace nSettings {
    Settings::Settings(QWidget* parent) : QWidget(parent) {
        logger = nLogger::Logger::getLogger();

        settings = std::make_shared<QSettings>();

        mainLayout = new QVBoxLayout(this);

        stackedWidget = new QStackedWidget(this);

        showBackground();

        mainSettings = new nMainSettings::MainSettings();
        gameSettings = new nGameSettings::GameSettings(settings);
        controlSettings = new nControlSettings::ControlSettings(settings);

        stackedWidget->addWidget(mainSettings);
        stackedWidget->addWidget(gameSettings);
        stackedWidget->addWidget(controlSettings);

        stackedWidget->setCurrentWidget(mainSettings);

        mainLayout->addWidget(stackedWidget);

        connect(mainSettings, &nMainSettings::MainSettings::switchToGameSettings, this, [=](){
            stackedWidget->setCurrentWidget(gameSettings);
        });
        connect(mainSettings, &nMainSettings::MainSettings::switchToControlSettings, this, [=](){
            stackedWidget->setCurrentWidget(controlSettings);
        });
        connect(mainSettings, &nMainSettings::MainSettings::switchToMenu, this, [=](){
            emit switchToMenu();
        });

        connect(gameSettings, &nGameSettings::GameSettings::switchToMainSettings, this, [=](){
            stackedWidget->setCurrentWidget(mainSettings);
        });
        connect(controlSettings, &nControlSettings::ControlSettings::switchToMainSettings, this, [=](){
            stackedWidget->setCurrentWidget(mainSettings);
        });

        logger->info("Класс Settings успешно инициализирован");
    }

    void Settings::showBackground() {
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
    }

    void Settings::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);
        if (!background.isNull()) {
            QPalette palette;
            QPixmap scaled = background.scaled(this->size(),
             Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
            palette.setBrush(QPalette::Window, scaled);
            this->setPalette(palette);
        }
    }

    unsigned int Settings::getHeight() const {
        return gameSettings->getHeight();
    }

    unsigned int Settings::getWidth() const {
        return gameSettings->getWidth();
    }

    std::shared_ptr<std::unordered_map<QString, int>> Settings::getKeys() {
        return controlSettings->getKeys();
    }
}