#include "mainwindow.h"

namespace nMainWindow {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    this->setWindowTitle("Snake game");
    this->resize(400, 300);
    
    QString imagePath = QCoreApplication::applicationDirPath() + "/../images/background.png";
    QPixmap background(imagePath);

    logger = Log::Logger::getLogger(); 

    if (background.isNull()) {
        logger->error("Не удалось подгрузить картинку, на задний фон экрана(главное меню)");
    } else {
        logger->info("Картинка успешно подгружена");
        QPalette palette;
        palette.setBrush(QPalette::Window, background.scaled(size(), Qt::IgnoreAspectRatio));
        this->setPalette(palette);
    }

    startGame = new QPushButton("Start Game!", this);
        
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignCenter);

    layout->addWidget(startGame);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QString imagePath = QCoreApplication::applicationDirPath() + "/../images/background.png";
    QPixmap background(imagePath);
    if (background.isNull()) {
        logger->error("Не удалось подгрузить картинку, на задний фон экрана(главное меню),"
                      "во время изменения размера экрана");
    } else {
        background = background.scaled(this->size(), Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation);
    
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(background));
        this->setPalette(palette);
    }
}

}
