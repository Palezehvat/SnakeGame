#include "internalssettings.h"

namespace nInternalsSettings {

    InternalsSettings::InternalsSettings(const QString& newText, const unsigned int newValue, const 
        unsigned int minValue, const unsigned int maxValue, QSlider* parent)
        : QSlider(Qt::Horizontal, parent), text(newText) {

        isHovered = false;
        value = newValue;

        this->setValue(newValue);
        this->setMinimum(minValue);
        this->setMaximum(maxValue);

        QString styleInternalsSettings = QString(R"(
            QSlider::groove:horizontal {
                background: %1;
            }
            QSlider::handle:horizontal {
                background: %2;
                width: 12px;
            }
        )").arg(UISettings::sliderGrooveBackgroundColor, UISettings::sliderHandleBackgroundColor);

        this->setStyleSheet(styleInternalsSettings);

        fontSize = 10;

        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        this->setFixedHeight(85);
        connect(this, &QSlider::valueChanged, this, [this](int v) {
            value = v;
            update();
        });
    }

    void InternalsSettings::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);
    
        int height = this->height();
        fontSize = std::min(height / 4.5, 40.0);

        update();
    }

    void InternalsSettings::paintEvent(QPaintEvent* event) {
        QSlider::paintEvent(event);
        
        QPainter p(this);

        QFont font;
        font.setBold(true);
        font.setPixelSize(fontSize);
        p.setFont(font);
        
        QPen pen(isHovered ? QColor("#1c89c4") : Qt::white);
        p.setPen(pen);
       
        setMouseTracking(true);
        p.drawText(this->rect(), Qt::AlignCenter, text + ": " + QString::number(value));       
    }

    void InternalsSettings::enterEvent(QEnterEvent* event) {
        isHovered = true;
        update();
        QSlider::enterEvent(event);
    }
    
    void InternalsSettings::leaveEvent(QEvent* event) {
        isHovered = false;
        update();
        QSlider::leaveEvent(event);
    }

    unsigned int InternalsSettings::getValue() const {
        return value;
    }
};