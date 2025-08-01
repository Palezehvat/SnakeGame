#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "logger.h"

namespace nScore {

class Score : public QWidget {
    Q_OBJECT

public:
    Score(QWidget* parent = nullptr);
    void updateCounter();

private:
    std::shared_ptr<spdlog::logger> logger;
    unsigned long long counter;
    QLabel* score = nullptr;
};

} // nScore

#endif // SCORE_H