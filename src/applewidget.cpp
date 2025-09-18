// applewidget.cpp
#include "applewidget.h"


namespace nAppleWidget {
    
    AppleWidget::AppleWidget(QWidget* parent) : QWidget(parent), counter(0) {
        logger = nLogger::Logger::getLogger();
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        counter = 0;
    }
    
    void AppleWidget::updateCounter() {
        ++counter;
        update();
    }

    void AppleWidget::restartCounter() {
        counter = 0;
        update();
    }
    
    void AppleWidget::drawApple(QPainter& p, QPoint center, const qreal r) {
        p.save();
        p.translate(center);

        // Яблоко //
        QPointF pTop(0, -r);
        QPointF pLeft(-r, 0);
        QPointF pBottom(0, r);
        QPointF pRight(r, 0);

        qreal dentTop = r * 0.3;
        qreal dentBottom = r * 0.15;

        QPainterPath applePath;
        applePath.moveTo(QPointF(pTop.x(), pTop.y() + dentTop));
        
        applePath.cubicTo(
            QPointF(-r * 0.5, -r),
            QPointF(-r, -r * 0.5), 
            pLeft
        );
        
        applePath.cubicTo(
            QPointF(-r, r * 0.5),
            QPointF(-r * 0.5, r),
            QPointF(pBottom.x(), pBottom.y() - dentBottom)
        );
        
        applePath.cubicTo(
            QPointF(r * 0.5, r),
            QPointF(r, r * 0.5),
            QPointF(pRight.x(), pRight.y())
        );
        
        applePath.cubicTo(
            QPointF(r, -r * 0.5),
            QPointF(r * 0.5, -r),
            QPointF(pTop.x(), pTop.y() + dentTop)
        );
        
        QLinearGradient bodyGrad(QPointF(-r, -r), QPointF(r, r));
        bodyGrad.setColorAt(0.0, QColor("#d63434"));
        bodyGrad.setColorAt(0.5, QColor("#ff4d4d"));
        bodyGrad.setColorAt(1.0, QColor("#d63434"));

        // Палка //
        qreal stemHeight = r * 0.6;
        qreal stemWidth  = r * 0.15;

        QPointF stemBase(pTop.x(), pTop.y() - dentBottom);
        
        QRectF stemRect(
            stemBase.x() - stemWidth / 2,
            stemBase.y(),
            stemWidth,
            stemHeight
        );

        QPainterPath stemPath;
        stemPath.addRect(stemRect);
        QLinearGradient stemGrad(stemRect.topLeft(), stemRect.bottomRight());
        stemGrad.setColorAt(0.0, QColor("#5a3c0a"));
        stemGrad.setColorAt(1.0, QColor("#8b5e2b"));

        p.setRenderHint(QPainter::Antialiasing, true);

        p.fillPath(stemPath, stemGrad);
        p.fillPath(applePath, bodyGrad);

        p.restore();
    }

    void AppleWidget::paintEvent(QPaintEvent* event) {
        QPainter p(this);
        p.fillRect(rect(), QColor(UISettings::colorBackgroundScore));
    
        const qreal r = std::min(this->height(), this->width()) / 5;
    
        QPoint appleCenter(this->width() / 4, this->height() / 2);

        drawApple(p, appleCenter, r);
    
        QRect textRect(
            appleCenter.x() + r * 1.5,
            appleCenter.y() - r,
            this->width() / 2,
            2 * r
        );

        QFont font = p.font();
        font.setPointSize(r * 0.8);
        p.setFont(font);
        p.setPen(Qt::white);
    
        p.drawText(textRect, Qt::AlignVCenter, QString::number(counter));
    }

};