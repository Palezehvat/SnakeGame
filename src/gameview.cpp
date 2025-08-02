#include "gameview.h"

namespace nGameView {

    GameView::GameView(nGameController::GameController* controller,
            int length, int width, int gameUpdateInterval, QWidget* parent) : QWidget(parent) {        
        logger = Log::Logger::getLogger();
        numberOfCellsLength = length;
        numberOfCellsWidth = width;
        this->controller = controller;
        this->sizeCell = nSettings::Settings::getSizeCell();
        this->gameUpdateIntervalForAnimation = gameUpdateInterval;

        setFocusPolicy(Qt::StrongFocus); // Чтобы нажатия клавиш регистрировало
        setFocus();

        frameTimer = new QTimer(this);
        connect(frameTimer, &QTimer::timeout, this, QOverload<>::of(&GameView::update));
        frameTimer->start(16);
        animationFrozen = false;
        logger->info("Класс GameView успешно инициализирован");
    }

    void GameView::stopAnimation() {
        frameTimer->stop();
        animationFrozen = true;
        update();
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

        qreal t = animationFrozen ? 1.0 : (qreal)(QDateTime::currentMSecsSinceEpoch() -
                                            lastMoveTime) / gameUpdateIntervalForAnimation;
        
        if (t > 1.0) t = 1.0;
        
        auto interpolatedBody = snake->getInterpolatedBody(t);
        if (interpolatedBody.size() != body.size()) { // Проверка на случай ошибки интерполяции
            return;
        }

        QPen snakePen(Qt::green); // Рисуем тело
        snakePen.setWidth(sizeCell * 0.8);
        snakePen.setCapStyle(Qt::RoundCap); // Скруглённые концы
        snakePen.setJoinStyle(Qt::RoundJoin); // Скруглённые углы
        painter.setPen(snakePen);

        QPainterPath snakePath;
        if (!interpolatedBody.empty()) {
            QPointF firstPoint(
                interpolatedBody[0].x() * sizeCell + sizeCell / 2,
                interpolatedBody[0].y() * sizeCell + sizeCell / 2
            );
            snakePath.moveTo(firstPoint);

            for (int i = 1; i < interpolatedBody.size() - 1; ++i) {
                QPointF p0(
                    interpolatedBody[i].x() * sizeCell + sizeCell / 2,
                    interpolatedBody[i].y() * sizeCell + sizeCell / 2
                );
                QPointF p1(
                    interpolatedBody[i + 1].x() * sizeCell + sizeCell / 2,
                    interpolatedBody[i + 1].y() * sizeCell + sizeCell / 2
                );

                QPointF controlPoint = (p0 + p1) / 2.0;

                snakePath.quadTo(p0, controlPoint);
            }

            // Добавляем хвост
            QPointF lastPoint(
                interpolatedBody.back().x() * sizeCell + sizeCell / 2,
                interpolatedBody.back().y() * sizeCell + sizeCell / 2
            );
            snakePath.lineTo(lastPoint);
        }

        painter.drawPath(snakePath);
    }

    void GameView::paintEvent(QPaintEvent*) {
        //logger->info("Начался процесс отрисовки доски");
        QPainter p(this);
        p.fillRect(rect(), Qt::black);

        int boardWidth = numberOfCellsWidth * sizeCell;
        int boardHeight = numberOfCellsLength * sizeCell;

        int offsetX = (width() - boardWidth) / 2;
        int offsetY = (height() - boardHeight) / 2;

        p.translate(offsetX, offsetY);

        QRect boardRect(0, 0, numberOfCellsWidth * sizeCell, numberOfCellsLength * sizeCell);
        p.setClipRect(boardRect);
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
        int w = event->size().width();
        int h = event->size().height();
        sizeCell = std::min(w / numberOfCellsWidth, h / numberOfCellsLength);
    
        update();
        logger->info("Размер игрового окна в GameView успешно изменён");
    }

    QSize GameView::minimumSizeHint() const {
        return QSize(numberOfCellsWidth * sizeCell, numberOfCellsLength * sizeCell);
    }
    
    QSize GameView::sizeHint() const {
        return minimumSizeHint();
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

    int GameView::getPreferredWidth() const {
        return numberOfCellsWidth * sizeCell;
    }
    
    int GameView::getPreferredHeight() const {
        return numberOfCellsLength * sizeCell;
    }

    void GameView::restart(int width, int length) {
        numberOfCellsLength = length;
        numberOfCellsWidth = width;
        frameTimer->start(16);
        animationFrozen = false;
    }
};