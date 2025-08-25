#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPalette>
#include "internalssettings.h"
#include "logger.h"
#include "uisettings.h"

namespace nSettings {

class Settings : public QWidget {
    Q_OBJECT

public:
    Settings(QWidget* parent = nullptr);
    unsigned int getHeight();
    unsigned int getWidth();

private:
    std::shared_ptr<spdlog::logger> logger;
    
    QGridLayout* grid = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    QPushButton* toSettings = nullptr;
    nInternalsSettings::InternalsSettings* boardWidth = nullptr;
    nInternalsSettings::InternalsSettings* boardHeight = nullptr;
    //nInternalsSettings::InternalsSettings* countRocks = nullptr;
    QPixmap background;

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:
    void switchToMenu();
};

} // namespace nSettings

#endif // SETTINGS_H
