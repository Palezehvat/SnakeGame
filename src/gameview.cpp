#include "gameview.h"

namespace nGameView {

    GameView::GameView(int sizeCell, int length, int width, QWidget* parent) : QWidget(parent){        
        logger = Log::Logger::getLogger();
        numberOfCellsLength = length;
        numberOfCellsWidth = width;
        this->sizeCell = sizeCell;
        logger->info("Класс GameView успешно инициализирован");
    }

    void GameView::drawFood(QPainter& p) {
        std::optional<QPoint> pos = food->getPosition();
        if (pos.has_value()) {
            QPoint position = pos.value();
            QRect rect(position.x() * sizeCell, position.y() * sizeCell, sizeCell, sizeCell);
            const QMap<nGameBoard::TypeCell, QPixmap>& textures = gameboard->getTextures();
            p.drawPixmap(rect, textures[nGameBoard::TypeCell::food]);
        }
        logger->info("Еда успешно отрисована");
    }

    void GameView::drawBoard(QPainter& p) {
        for (int i = 0; i < numberOfCellsWidth; ++i) {
            for (int j = 0; j < numberOfCellsLength; ++j) {
                const nGameBoard::Cell& cell = gameboard->getCell(i, j);
                QRect rect(i * sizeCell, j * sizeCell, sizeCell, sizeCell);
                const QMap<nGameBoard::TypeCell, QPixmap>& textures = gameboard->getTextures();
                p.drawPixmap(rect, textures[nGameBoard::TypeCell::grass]);
            }
        }
        logger->info("Доска успешно отрисована");
    }

    void GameView::paintEvent(QPaintEvent*) {
        logger->info("Начался процесс отрисовки доски");
        QPainter p(this);
        drawBoard(p);
        if (food) {
            logger->info("Начался процесс отрисовки еды");
            drawFood(p);
        }
    }

    void GameView::resizeEvent(QResizeEvent* event) {
        int w = this->width();
        int h = this->height();

        sizeCell = std::min(w / numberOfCellsWidth, h / numberOfCellsLength);
        update();
        logger->info("Размер игрового окна в GameView успешно изменён");
    }

    QSize GameView::sizeHint() const {
        return QSize(400, 400);
    }

    void GameView::setGameBoard(std::shared_ptr<nGameBoard::GameBoard> board) {
        gameboard = board;
    }

    void GameView::setFood(std::shared_ptr<nFood::Food> food) {
        this->food = food;
    }
};