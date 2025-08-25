#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include "logger.h"
#include "applewidget.h"
#include "uisettings.h"

namespace nScore {

class Score : public QWidget {
    Q_OBJECT

public:
    Score(QWidget* parent = nullptr);
    void updateCounter();
    void restart();
    void showGameOverScreen();

private:
    std::shared_ptr<spdlog::logger> logger;
    unsigned long long counter;
    QPushButton* restartButton = nullptr;
    QPushButton* menuButton = nullptr;
    QPushButton* pauseButton = nullptr;
    std::unique_ptr<nAppleWidget::AppleWidget> apple = nullptr;

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

signals:
    void backToMenu();
    void restartGame();
    void pause();

};

} // nScore

#endif // SCORE_H