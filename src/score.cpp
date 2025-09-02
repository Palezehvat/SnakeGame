#include "score.h"

namespace nScore {

    Score::Score(QWidget* parent) : QWidget(parent) {
        logger = Log::Logger::getLogger();
        apple = std::make_unique<nAppleWidget::AppleWidget>();
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
        unsigned int gameWidth  = UISettings::maxWidth  * UISettings::currentSizeCell;
        unsigned int gameHeight = UISettings::maxHeight * UISettings::currentSizeCell;
        unsigned int scoreWidth = gameWidth / 4;
        setMinimumSize(scoreWidth, gameHeight);
    
        restartButton = new QPushButton(this);
        menuButton = new QPushButton(this);
        pauseButton =  new QPushButton(this);
        restartButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        menuButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        pauseButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        restartButton->setText("Заново");
        menuButton->setText("Меню");
        pauseButton->setText("Пауза");

        QString styleButtonsInScore = QString(R"(
            QPushButton {
                background: %1;
                border: 2px solid %2;
            }
            QPushButton:hover {
                background-color: %3
            }
        )").arg(UISettings::backgroundButtonInScoreColor, UISettings::borderButtonInScoreColor,
                UISettings::hoverButtonInScoreColor);

        restartButton->setStyleSheet(styleButtonsInScore);
        menuButton->setStyleSheet(styleButtonsInScore);
        pauseButton->setStyleSheet(styleButtonsInScore);
    
        QVBoxLayout* layout = new QVBoxLayout(this);

        apple->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(apple.get(), 20);
        layout->addWidget(pauseButton, 2);
    
        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(restartButton);
        buttonLayout->addWidget(menuButton);
    
        layout->addLayout(buttonLayout, 2);
    
        setLayout(layout);
    
        connect(restartButton, &QPushButton::clicked, this, &Score::restartGame);
        connect(menuButton, &QPushButton::clicked, this, &Score::backToMenu);
        connect(pauseButton, &QPushButton::clicked, this, &Score::pause);
    
        counter = 0;
    }

    void Score::paintEvent(QPaintEvent* event) {
        QPainter p(this);
        p.fillRect(rect(), QColor(UISettings::colorBackgroundScore));
    }

    void Score::resizeEvent(QResizeEvent* event) {
        QWidget::resizeEvent(event);

        QFont fontRestartButton = UISettings::workWithButton(restartButton);
        QFont fontMenuButton = UISettings::workWithButton(menuButton);
        
        int minSizeFont = std::min(fontMenuButton.pointSize(), fontRestartButton.pointSize());
        QFont commonFont = fontMenuButton;
        commonFont.setPointSize(minSizeFont);

        menuButton->setFont(commonFont);
        restartButton->setFont(commonFont);
        pauseButton->setFont(commonFont);

        //QFont fontPauseButton = workWithButton(pauseButton);
    }

    void Score::showGameOverScreen() {
        ;
    }

    void Score::updateCounter() {
        apple->updateCounter();
        update();
    }

    void Score::restart() {
        apple->restartCounter();
        update();
    }
};