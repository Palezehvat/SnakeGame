#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPalette>
#include <QStackedWidget>
#include <QSettings>
#include "logger.h"
#include "mainsettings.h"
#include "gamesettings.h"
#include "controlsettings.h"

namespace nSettings {

class Settings : public QWidget {
    Q_OBJECT

public:
    Settings(QWidget* parent = nullptr);
    unsigned int getHeight() const;
    unsigned int getWidth() const;
    std::shared_ptr<std::unordered_map<QString, int>> getKeys();

private:
    std::shared_ptr<spdlog::logger> logger;
    nMainSettings::MainSettings* mainSettings = nullptr;
    nGameSettings::GameSettings* gameSettings = nullptr;
    nControlSettings::ControlSettings* controlSettings = nullptr;
    std::shared_ptr<QSettings> settings = nullptr;
    QStackedWidget* stackedWidget = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPixmap background;

    void showBackground();

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void switchToMenu();
};

} // namespace nSettings

#endif // SETTINGS_H
