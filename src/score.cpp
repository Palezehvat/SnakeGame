#include "score.h"

namespace nScore {

    Score::Score(QWidget* parent) {
        logger = Log::Logger::getLogger();
        
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        score = new QLabel(this);
        score->setStyleSheet("color: red; background-color: blue;");
        score->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(score);

        counter = 0;
        score->setText(QString::number(counter));
        score->setAlignment(Qt::AlignHCenter);
    }

    void Score::updateCounter() {
        ++counter;
        score->setText(QString::number(counter));
    }

    void Score::restart() {
        counter = 0;
        score->setText(QString::number(counter));
    }
};