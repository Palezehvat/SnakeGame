#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCoreApplication>
#include "logger.h"

namespace nSettings {

class Settings : public QWidget {
    Q_OBJECT

public:
    Settings(QWidget* parent = nullptr);
    int getLength() {return length;};
    int getWidth() {return width;};

private:
    std::shared_ptr<spdlog::logger> logger;
    void resizeEvent(QResizeEvent* event) override;
    int length = 5;
    int width = 5;
    //int sizeRocks = 0;

signals:
    void switchToMenu();
};

} // namespace nSettings

#endif // SETTINGS_H
