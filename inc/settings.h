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
    static int getLength();
    static int getWidth();

private:
    std::shared_ptr<spdlog::logger> logger;
    void resizeEvent(QResizeEvent* event) override;
    static int length;
    static int width;
    //int sizeRocks = 0;

signals:
    void switchToMenu();
};

} // namespace nSettings

#endif // SETTINGS_H
