#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include "score.h"
#include "logger.h"

namespace nGameView {
    class GameView;
}

namespace nGamePanel {

class GamePanel : public QWidget {
    Q_OBJECT

public:
    GamePanel(std::shared_ptr<nGameView::GameView> board,
              std::shared_ptr<nScore::Score> score, QWidget* parent = nullptr);
    std::shared_ptr<nGameView::GameView> getBoard() const;
    void restart();

private:
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<nGameView::GameView> board;
    std::shared_ptr<nScore::Score> score;

    QHBoxLayout* layout = nullptr;

signals:
    void backToMenu();
    void restartGame();
    void gameOver();

};

}; // nGamePanel

#endif // GAMEPANEL_H