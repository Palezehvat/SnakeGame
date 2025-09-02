#ifndef CONTROLSETTINGS_H
#define CONTROLSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>
#include "logger.h"
#include "keybindwidget.h"
#include "uisettings.h"

namespace nControlSettings {

class ControlSettings : public QWidget {
    Q_OBJECT

public:
    ControlSettings(std::shared_ptr<QSettings> settings, QWidget* parent = nullptr);
    std::shared_ptr<std::unordered_map<QString, int>> getKeys();

private:
    std::shared_ptr<spdlog::logger> logger;
    QGridLayout* grid = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPushButton* toMainSettings = nullptr;
    QLabel* titleSettings = nullptr;
    nKeyBindWidget::KeyBindWidget* left = nullptr;
    nKeyBindWidget::KeyBindWidget* right = nullptr;
    nKeyBindWidget::KeyBindWidget* up = nullptr;
    nKeyBindWidget::KeyBindWidget* down = nullptr;
    nKeyBindWidget::KeyBindWidget* pause = nullptr;
    nKeyBindWidget::KeyBindWidget* restart = nullptr;
    std::shared_ptr<QSettings>  settings = nullptr;
    std::shared_ptr<std::unordered_map<QString, int>> keys;

    void firstCreateConfig();

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void switchToMainSettings();
};

} // namespace nSettings

#endif // CONTROLSETTINGS_H
