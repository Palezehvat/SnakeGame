#ifndef INTERNALSSETTINGS_H
#define INTERNALSSETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QPainter>
#include <QEvent>
#include "uisettings.h"
#include "logger.h"

namespace nInternalsSettings {

class InternalsSettings : public QSlider {
    Q_OBJECT

public:
    InternalsSettings(const QString& newText, const unsigned int newValue, const 
        unsigned int newMinValue, const unsigned int newMaxValue, QSlider* parent = nullptr);

    void resizeEvent(QResizeEvent* event);
    unsigned int getValue() const;

private:
    unsigned int value;
    double fontSize = 0;
    QString text;
    bool isHovered;

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
};

}

#endif //INTERNALSSETTINGS_H