#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "logger.h"
#include "uisettings.h"

namespace nMainSettings {

class MainSettings : public QWidget {
    Q_OBJECT

public:
    MainSettings(QWidget* parent = nullptr);

private:
    std::shared_ptr<spdlog::logger> logger;
    QGridLayout* grid = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPushButton* toMenu = nullptr;
    QPushButton* toControlSettings = nullptr;
    QPushButton* toGameSettings = nullptr;
    QLabel* titleSettings = nullptr;

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void switchToMenu();
    void switchToControlSettings();
    void switchToGameSettings();
};

} // namespace nMainSettings

#endif // MAINSETTINGS_H
