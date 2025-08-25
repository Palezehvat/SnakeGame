#include "gameview.h"

namespace nGameView {

    GameView::GameView(nGameController::GameController* controller,
         int gameUpdateInterval, QWidget* parent) : QWidget(parent) {        
        logger = Log::Logger::getLogger();

        sizeCell = UISettings::currentSizeCell;
        maximumNumberOfCellsInWidth = UISettings::maxWidth;
        maximumNumberOfCellsInHeight = UISettings::maxHeight;

        colorEvenField = QColor(UISettings::colorEvenFieldInGame);
        colorOddField = QColor(UISettings::colorOddFieldInGame);
        colorBackground = QColor(UISettings::colorBackgroundInGame);
        
        this->controller = controller;
        this->gameUpdateIntervalMs = gameUpdateInterval;

        setFocusPolicy(Qt::StrongFocus); // Чтобы нажатия клавиш регистрировало
        setFocus();

        frameTimer = new QTimer(this);
        connect(frameTimer, &QTimer::timeout, this, QOverload<>::of(&GameView::update));
        frameTimer->start(16);
        animationFrozen = false;
        logger->info("Класс GameView успешно инициализирован");
    }

    void GameView::drawApple(QPainter& p, QPointF center) {
        p.save();
        p.translate(center);

        const qreal r = sizeCell / 3.0;

        // Яблоко //
        QPointF pTop(0, -r);
        QPointF pLeft(-r, 0);
        QPointF pBottom(0, r);
        QPointF pRight(r, 0);

        qreal dentTop = r * 0.3;
        qreal dentBottom = r * 0.15;

        QPainterPath applePath;
        applePath.moveTo(QPointF(pTop.x(), pTop.y() + dentTop));
        
        applePath.cubicTo(
            QPointF(-r * 0.5, -r),
            QPointF(-r, -r * 0.5), 
            pLeft
        );
        
        applePath.cubicTo(
            QPointF(-r, r * 0.5),
            QPointF(-r * 0.5, r),
            QPointF(pBottom.x(), pBottom.y() - dentBottom)
        );
        
        applePath.cubicTo(
            QPointF(r * 0.5, r),
            QPointF(r, r * 0.5),
            QPointF(pRight.x(), pRight.y())
        );
        
        applePath.cubicTo(
            QPointF(r, -r * 0.5),
            QPointF(r * 0.5, -r),
            QPointF(pTop.x(), pTop.y() + dentTop)
        );
        
        QLinearGradient bodyGrad(QPointF(-r, -r), QPointF(r, r));
        bodyGrad.setColorAt(0.0, QColor("#d63434"));
        bodyGrad.setColorAt(0.5, QColor("#ff4d4d"));
        bodyGrad.setColorAt(1.0, QColor("#d63434"));

        // Палка //
        qreal stemHeight = r * 0.6;
        qreal stemWidth  = r * 0.15;

        QPointF stemBase(pTop.x(), pTop.y() - dentBottom);
        
        QRectF stemRect(
            stemBase.x() - stemWidth / 2,
            stemBase.y(),
            stemWidth,
            stemHeight
        );

        QPainterPath stemPath;
        stemPath.addRect(stemRect);
        QLinearGradient stemGrad(stemRect.topLeft(), stemRect.bottomRight());
        stemGrad.setColorAt(0.0, QColor("#5a3c0a"));
        stemGrad.setColorAt(1.0, QColor("#8b5e2b"));

        p.setRenderHint(QPainter::Antialiasing, true);

        p.fillPath(stemPath, stemGrad);
        p.fillPath(applePath, bodyGrad);

        p.restore();
    }

    void GameView::drawFood(QPainter& p) {
        std::optional<QPoint> pos = food->getPosition();
        if (pos.has_value()) {
            QPointF position = pos.value();
            position = {position.x() * sizeCell + sizeCell / 2, position.y() * sizeCell + sizeCell / 2};
            drawApple(p, position);
        }
        //logger->info("Еда успешно отрисована");
    }

    void GameView::drawBoard(QPainter& p) {
        for (int i = 0; i < maximumNumberOfCellsInWidth; ++i) {
            for (int j = 0; j < maximumNumberOfCellsInHeight; ++j) {
                const nGameBoard::Cell& cell = gameboard->getCell(i, j);
                QRect rect(i * sizeCell, j * sizeCell, sizeCell, sizeCell);
                if (cell.type != nGameBoard::TypeCell::background) {
                    bool isEven = ((cell.row + cell.col) % 2) == 0;
                    p.fillRect(rect, isEven ? colorEvenField : colorOddField);
                } else {
                    p.fillRect(rect, colorBackground);
                }
            }
        }
        //logger->info("Доска успешно отрисована");
    }

    qreal getAngleForDirection(nSnake::Movement direction) {
        switch (direction) {
            case nSnake::Movement::Up: return -90;
            case nSnake::Movement::Down: return 90;
            case nSnake::Movement::Left: return 180;
            case nSnake::Movement::Right: return 0;
        }
        return 0;
    }

    void GameView::drawEyes(QPainter& p, QPointF p1, QPointF p2) {
        p.save();

        QPointF center = (p1 + p2) / 2.0;
        p.translate(center);

        qreal eyeAngle = std::atan2(p2.y() - p1.y(), p2.x() - p1.x()) * 180.0 / M_PI;
        p.rotate(eyeAngle);
        
        qreal widthEyes = sizeCell / 7;
        qreal heightEyes = sizeCell / 7;

        p.setBrush(QColor("#e8ba31"));
        p.setPen(Qt::NoPen);
        p.drawEllipse(QPointF(0, 0), heightEyes, widthEyes);
        p.setBrush(Qt::black);
        p.drawEllipse(QPointF(0, 0), heightEyes, widthEyes / 3);

        p.restore();
    }

    void GameView::drawRotatedHead(QPainter& p, QPointF center, qreal angle) {
        p.save();
        p.translate(center);
        p.rotate(angle);
        
        QPainterPath headPath;
        const qreal epsilon = sizeCell / 10;

        QPointF p1 = { -sizeCell / 2, sizeCell / 6 };
        QPointF p2 = { -sizeCell / 6, sizeCell / 2 - epsilon };
        QPointF p3 = { sizeCell / 2 - epsilon,  sizeCell / 6 };
        QPointF p4 = { sizeCell / 2 - epsilon,  -sizeCell / 6 };
        QPointF p5 = { -sizeCell / 6, -sizeCell / 2 + epsilon };
        QPointF p6 = { -sizeCell / 2, -sizeCell / 6 };

        headPath.moveTo(p1);
        headPath.cubicTo(p1 + (p2 - p6) / 6, p2 - (p3 - p1) / 6, p2);
        headPath.cubicTo(p2 + (p3 - p1) / 6, p3 - (p4 - p2) / 6, p3);
        headPath.cubicTo(p3 + (p4 - p2) / 6, p4 - (p5 - p3) / 6, p4);
        headPath.cubicTo(p4 + (p5 - p3) / 6, p5 - (p6 - p4) / 6, p5);
        headPath.cubicTo(p5 + (p6 - p4) / 6, p6 - (p1 - p5) / 6, p6);
        headPath.cubicTo(p6 + (p1 - p5) / 6, p1 - (p2 - p6) / 6, p1);

        QPointF nose(sizeCell / 2, 0);
        QPointF back(-sizeCell / 2, 0);

        QLinearGradient headGradient(back, nose);
        headGradient.setColorAt(0.0, QColor("#278017"));
        headGradient.setColorAt(0.5, QColor("#23c706"));
        headGradient.setColorAt(1.0, QColor("#278017"));
                
        p.fillPath(headPath, QBrush(headGradient));
        
        // Глаз. Странный вариант
        
        // qreal widthEyes = sizeCell / 6;
        // qreal heightEyes = sizeCell / 3;
        
        // p.setBrush(Qt::white);
        // p.setPen(Qt::NoPen);
        // p.drawEllipse((p3 - p2) / 2, widthEyes, heightEyes);
        // p.drawEllipse((p4 - p3) / 2, widthEyes, heightEyes);
        // p.setBrush(Qt::black);
        // p.drawEllipse((p3 - p2) / 2, widthEyes / 4, heightEyes / 4);
        // p.drawEllipse((p4 - p3) / 2, widthEyes / 4, heightEyes / 4);
        
        drawEyes(p, p2, p3);
        drawEyes(p, p4, p5);

        p.restore();
    }

    static qreal normalizeAngleDeg(qreal a) {
        while (a <= -180.0) a += 360.0;
        while (a >  180.0) a -= 360.0;
        return a;
    }

    void GameView::stopAnimation() {
        animationFrozen = true;
        pausedT = (qreal)(QDateTime::currentMSecsSinceEpoch() 
                                  - lastMoveTime) / gameUpdateIntervalMs;
        update();
        this->setFocus(Qt::OtherFocusReason);
    }

    void GameView::continueAnimation() {
        animationFrozen = false;
        this->setFocus(Qt::OtherFocusReason);
    }
    
    void GameView::drawSnake(QPainter& painter) {
        auto body = snake->getBody();
        if (body.empty()) return;
    
        qreal t = (qreal)(QDateTime::currentMSecsSinceEpoch() - lastMoveTime) / gameUpdateIntervalMs;
        if (t > 1.0) t = 1.0;
    
        auto interpolatedBody = snake->getInterpolatedBody(t);
        if (interpolatedBody.size() < 2) return;

        const qreal widthBody = sizeCell * 0.5;

        QPointF tailPoint(
            interpolatedBody[0].x() * sizeCell + sizeCell / 2,
            interpolatedBody[0].y() * sizeCell + sizeCell / 2
        ); // точка хвоста
        
        QPointF headPoint(
            interpolatedBody.back().x() * sizeCell + sizeCell / 2,
            interpolatedBody.back().y() * sizeCell + sizeCell / 2
        ); // точка головы

        QLinearGradient gradient(tailPoint, headPoint);

        gradient.setColorAt(0.0, QColor("#278017"));
        gradient.setColorAt(0.5, QColor("#23c706"));
        gradient.setColorAt(1.0, QColor("#278017"));
    
        QPen snakePen(QBrush(gradient), widthBody);
        snakePen.setWidthF(widthBody);
        snakePen.setCapStyle(Qt::RoundCap);
        snakePen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(snakePen);
        painter.setRenderHint(QPainter::Antialiasing);
    
        // Хвост
        QPainterPath snakePath;
        snakePath.moveTo(tailPoint);
    
        // Тело
        for (int i = 0; i < interpolatedBody.size() - 1; ++i) {
            QPointF p0(interpolatedBody[i].x() * sizeCell + sizeCell / 2,
                       interpolatedBody[i].y() * sizeCell + sizeCell / 2);
            QPointF p1(interpolatedBody[i + 1].x() * sizeCell + sizeCell / 2,
                       interpolatedBody[i + 1].y() * sizeCell + sizeCell / 2);
            QPointF control = (p0 + p1) / 2.0;
            snakePath.quadTo(p0, control);
        }
        
        // Шея
        QPointF neckPoint(
            interpolatedBody[interpolatedBody.size()-2].x() * sizeCell + sizeCell / 2,
            interpolatedBody[interpolatedBody.size()-2].y() * sizeCell + sizeCell / 2
        );
    
        qreal targetAngle = std::atan2(headPoint.y() - neckPoint.y(),
                                       headPoint.x() - neckPoint.x()) * 180.0 / M_PI;
    
        if (!headAngleInitialized) {
            headRenderAngle = targetAngle;
            headAngleInitialized = true;
        }
    
        qreal delta = normalizeAngleDeg(targetAngle - headRenderAngle);
    
        qreal smoothingFactor = 0.50;
        headRenderAngle += delta * smoothingFactor;
    
        QPointF localBase(-sizeCell/2 * 0.8, 0.0);

        QTransform rot;
        rot.rotate(headRenderAngle);
        QPointF basePoint = headPoint + rot.map(localBase);
    
        snakePath.lineTo(basePoint);
    
        painter.drawPath(snakePath);
    
        drawRotatedHead(painter, headPoint, headRenderAngle);
    }

    void GameView::paintEvent(QPaintEvent*) {
        //logger->info("Начался процесс отрисовки доски");
        QPainter p(this);
        p.fillRect(rect(), colorBackground);

        int boardWidth = maximumNumberOfCellsInWidth * sizeCell;
        int boardHeight = maximumNumberOfCellsInHeight * sizeCell;

        int offsetX = (width() - boardWidth) / 2;
        int offsetY = (height() - boardHeight) / 2;

        p.translate(offsetX, offsetY);

        QRect boardRect(0, 0, maximumNumberOfCellsInWidth * sizeCell,
                        maximumNumberOfCellsInHeight * sizeCell);
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
        sizeCell = std::min(w / maximumNumberOfCellsInWidth, h / maximumNumberOfCellsInHeight);
    
        update();
        logger->info("Размер игрового окна в GameView успешно изменён");
    }

    QSize GameView::minimumSizeHint() const {
        return QSize(maximumNumberOfCellsInWidth * sizeCell, maximumNumberOfCellsInHeight * sizeCell);
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
        return maximumNumberOfCellsInWidth * sizeCell;
    }
    
    int GameView::getPreferredHeight() const {
        return maximumNumberOfCellsInHeight * sizeCell;
    }

    void GameView::restart() {
        frameTimer->start(16);
        animationFrozen = false;
        this->setFocus(Qt::OtherFocusReason);
    }
};