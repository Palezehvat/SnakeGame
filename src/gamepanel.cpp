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
        connect(score.get(), &nScore::Score::restartGame, this, &GamePanel::restartGame);
        connect(score.get(), &nScore::Score::backToMenu, this, &GamePanel::backToMenu);
    }

    std::shared_ptr<nGameView::GameView> GamePanel::getBoard() const {
        return board;
    }
};