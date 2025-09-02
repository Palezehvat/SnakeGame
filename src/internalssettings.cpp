#include "internalssettings.h"

namespace nInternalsSettings {

    InternalsSettings::InternalsSettings(const QString& newText, const unsigned int newValue, const 
        unsigned int minValue, const unsigned int maxValue, const QString& settingsPlace,
        std::shared_ptr<QSettings> settings, QSlider* parent) : QSlider(Qt::Horizontal, parent),
        text(newText), settingsPlace(settingsPlace), settings(settings) {

        logger = Log::Logger::getLogger();

        isHovered = false;

        if (newValue >= minValue && newValue <= maxValue) {
            this->setValue(newValue);
            this->setMinimum(minValue);
            this->setMaximum(maxValue);
            value = newValue;
        } else {
            logger->error(fmt::format("Неверная конфигурация.{}: {}.Переход к настройке по умолчанию.",
                          text.toStdString(), std::to_string(newValue)));
            this->setValue(maxValue);
            this->setMinimum(minValue);
            this->setMaximum(maxValue);
            value = maxValue;
            settings->setValue(settingsPlace, value);
        }

        int handleWidth = std::max(4, this->width() / 10);

        QString styleInternalsSettings = QString(R"(
            QSlider::groove:horizontal {
                background: %1;
            }
            QSlider::handle:horizontal {
                background: %2;
                width: %3px;
            }
        )").arg(UISettings::sliderGrooveBackgroundColor, UISettings::sliderHandleBackgroundColor)
           .arg(handleWidth);

        this->setStyleSheet(styleInternalsSettings);

        fontSize = height() / 10;

        this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        connect(this, &QSlider::valueChanged, this, [this](int v) {
            this->settings->setValue(this->settingsPlace, v);
            value = v;
            update();
        });
    }

    void InternalsSettings::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);

        int handleWidth = std::max(4, this->width() / 10);

        QString styleInternalsSettings = QString(R"(
            QSlider::groove:horizontal {
                background: %1;
            }
            QSlider::handle:horizontal {
                background: %2;
                width: %3px;
            }
        )").arg(UISettings::sliderGrooveBackgroundColor,
                UISettings::sliderHandleBackgroundColor)
           .arg(handleWidth);
    
        this->setStyleSheet(styleInternalsSettings);

        QFont font = UISettings::findBestSizeFont(this->height(), this->width(), this->font(),
                                                  text + ": " + QString::number(value));
        fontSize = font.pointSizeF();

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