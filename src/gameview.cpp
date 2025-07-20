#include "gameview.h"

namespace nGameView {

    GameView::GameView(nGameController::GameController* controller,
            int length, int width, int gameUpdateInterval, QWidget* parent) : QWidget(parent) {        
        logger = Log::Logger::getLogger();
        numberOfCellsLength = length;
        numberOfCellsWidth = width;
        this->controller = controller;
        this->sizeCell = sizeCell;
        this->gameUpdateIntervalForAnimation = gameUpdateInterval;

        QPushButton* restartButton = new QPushButton("Начать заново", this);
        QPushButton* menuButton = new QPushButton("В меню", this);

        restartButton->move(200, 100);
        menuButton->move(200, 200);

        restartButton->hide();
        menuButton->hide();

        connect(restartButton, &QPushButton::clicked, this, &GameView::restartGame);
        connect(menuButton, &QPushButton::clicked, this, &GameView::backToMenu);

        this->restartButton = restartButton;
        this->menuButton = menuButton;

        frameTimer = new QTimer(this);
        connect(frameTimer, &QTimer::timeout, this, QOverload<>::of(&GameView::update));
        frameTimer->start(16);

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
        //logger->info("Еда успешно отрисована");
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
        //logger->info("Доска успешно отрисована");
    }

    void GameView::drawSnake(QPainter& painter) {
        auto body = snake->getBody();
        if (body.empty()) {
            return;
        }
    
        nSnake::Movement currentDirection = snake->getCurrentDirection();

        qreal t = (qreal)(QDateTime::currentMSecsSinceEpoch() - lastMoveTime) / gameUpdateIntervalForAnimation;
        if (t > 1.0) t = 1.0;
        
        auto interpolatedBody = snake->getInterpolatedBody(t);
        if (interpolatedBody.size() != body.size()) { // Проверка на случай ошибки интерполяции
            return;
        }
    
        const auto& textures = gameboard->getTextures();
        const int segmentCount = body.size();
    
        for (int i = 0; i < segmentCount; ++i) {
            nGameBoard::TypeCell type;
    
            if (i == segmentCount - 1) { // Голова
                QPoint headDir = (segmentCount > 1) ? (body[i] - body[i-1]) : QPoint(1, 0);
                if (headDir.x() > 0) type = nGameBoard::headRight;
                else if (headDir.x() < 0) type = nGameBoard::headLeft;
                else if (headDir.y() > 0) type = nGameBoard::headDown;
                else type = nGameBoard::headUp;
            } else if (i == 0) { // Хвост
                QPoint tailDir = body[i+1] - body[i]; // Направление от хвоста к следующему сегменту
                if (tailDir.x() > 0) type = nGameBoard::tailRight;
                else if (tailDir.x() < 0) type = nGameBoard::tailLeft;
                else if (tailDir.y() > 0) type = nGameBoard::tailDown;
                else type = nGameBoard::tailUp;
            } else {
                QPoint dirFromPrev = body[i] - body[i-1];
                QPoint dirToNext = body[i+1] - body[i];

                
                if (dirFromPrev == dirToNext) {
                    type = (dirFromPrev.x() != 0) ? nGameBoard::bodyHorizontal : nGameBoard::bodyVertical;
                } else {
                    bool fromUp = (dirFromPrev.y() > 0);
                    bool fromDown = (dirFromPrev.y() < 0);
                    bool fromLeft = (dirFromPrev.x() > 0);
                    bool fromRight = (dirFromPrev.x() < 0);
    
                    bool toUp = (dirToNext.y() < 0);
                    bool toDown = (dirToNext.y() > 0);
                    bool toLeft = (dirToNext.x() < 0);
                    bool toRight = (dirToNext.x() > 0);


    
                    if ((fromDown && toRight) || (fromRight && toDown)) {
                        // Форма угла: ┌
                        type = nGameBoard::bodyRight; 
                    } else if ((fromDown && toLeft) || (fromLeft && toDown)) {
                        // Форма угла: ┐
                        type = nGameBoard::bodyDown;
                    } else if ((fromUp && toLeft) || (fromLeft && toUp)) {
                        // Форма угла: ┘
                        type = nGameBoard::bodyLeft;
                    } else { // (fromUp && toRight) || (fromRight && toUp)
                        // Форма угла: └
                        type = nGameBoard::bodyUp;
                    }
                }
            }
            
            // --- Логика отрисовки ---
            QPointF currentPos = interpolatedBody[i];
            QRectF targetRect(currentPos.x() * sizeCell, currentPos.y() * sizeCell, sizeCell, sizeCell);
    
            painter.drawPixmap(targetRect.toRect(), textures.value(type));
        }
    }


    void GameView::paintEvent(QPaintEvent*) {
        //logger->info("Начался процесс отрисовки доски");
        QPainter p(this);
        drawBoard(p);
        if (food) {
            //logger->info("Начался процесс отрисовки еды");
            drawFood(p);
        }

        if (snake) {
            //logger->info("Начался процесс отрисовки змеи");
            drawSnake(p);
            //logger->info("Отрисовка змеи закончена");
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

    void GameView::setSnake(std::shared_ptr<nSnake::Snake> snake) {
        this->snake = snake;
    }

    void GameView::setLastMoveTime(qint64 lastMoveTime) {
        this->lastMoveTime = lastMoveTime;
    }

    void GameView::showGameOverScreen() {
        restartButton->show();
        menuButton->show();
    }

    void GameView::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
            case Qt::Key_Up:
                controller->changeDirection(nSnake::Movement::Up);
                break;
            case Qt::Key_Down:
                controller->changeDirection(nSnake::Movement::Down);
                break;
            case Qt::Key_Left:
                controller->changeDirection(nSnake::Movement::Left);
                break;
            case Qt::Key_Right:
                controller->changeDirection(nSnake::Movement::Right);
                break;
            default:
                QWidget::keyPressEvent(event);
        }
    }
};