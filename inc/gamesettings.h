#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSettings>
#include "internalssettings.h"
#include "logger.h"
#include "uisettings.h"

namespace nGameSettings {

class GameSettings : public QWidget {
    Q_OBJECT

public:
    GameSettings(std::shared_ptr<QSettings> settings, QWidget* parent = nullptr);
    unsigned int getHeight() const;
    unsigned int getWidth() const;

private:
    std::shared_ptr<spdlog::logger> logger = nullptr;
    nInternalsSettings::InternalsSettings* boardWidth = nullptr;
    nInternalsSettings::InternalsSettings* boardHeight = nullptr;
    QLabel* titleSettings = nullptr;
    QGridLayout* grid = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPushButton* toMainSettings = nullptr;
    std::shared_ptr<QSettings> settings = nullptr;

    void firstCreateConfig();

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void switchToMainSettings();
};

} // namespace nGameSettings

#endif // GAMESETTINGS_H