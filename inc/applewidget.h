#ifndef APPLEWIDGET_H
#define APPLEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include "logger.h"
#include "uisettings.h"

namespace nAppleWidget {

class AppleWidget : public QWidget {
    Q_OBJECT
public:
    AppleWidget(QWidget* parent = nullptr);
    void updateCounter();
    void restartCounter();
    
protected:
    void paintEvent(QPaintEvent* event) override;
    
private:
    std::shared_ptr<spdlog::logger> logger;
    int counter;

    void drawApple(QPainter& p, QPoint center, const qreal r);
};

};


#endif // APPLEWIDGET_H