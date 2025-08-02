#include "gameview.h"
#include "score.h"
#include "gamepanel.h"

namespace nGamePanel {

    GamePanel::GamePanel(std::shared_ptr<nGameView::GameView> board,
        std::shared_ptr<nScore::Score> score, QWidget* parent) {
        
        logger = Log::Logger::getLogger();
        
        this->score = score;
        this->board = board;
        layout = new QHBoxLayout(this);
        
        board->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        score->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        layout->addWidget(board.get());
        layout->addWidget(score.get());
        layout->setStretch(0, 3);
        layout->setStretch(1, 1);

        restartButton = new QPushButton("Начать заново", this);
        menuButton = new QPushButton("В меню", this);

        restartButton->move(200, 100);
        menuButton->move(200, 200);

        restartButton->hide();
        menuButton->hide();

        connect(restartButton, &QPushButton::clicked, this, &GamePanel::restartGame);
        connect(menuButton, &QPushButton::clicked, this, &GamePanel::backToMenu);
    }

    void GamePanel::showGameOverScreen() {
        restartButton->show();
        menuButton->show();
    }

    std::shared_ptr<nGameView::GameView> GamePanel::getBoard() const {
        return board;
    }

    void GamePanel::restart() {
        restartButton->hide();
        menuButton->hide();
    }
};